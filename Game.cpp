#include "Game.h"

Game::Game(sf::Vector2i screenSize)
    :player(new Player()), window(sf::VideoMode(screenSize.x, screenSize.y), "Jeu", sf::Style::Default), sendDatatThread(&Game::sendData, this), receiveDatatThread(&Game::receiveData, this), sendThreadStarted(false), receiveThreadStarted(false)
{
    exWeapon = new Weapon();
    window.setFramerateLimit(30);
    player->setPosition(200, 200);
    map.load("map.txt");
    ip = sf::IpAddress::getPublicAddress(sf::seconds(5));
}

void Game::run()
{
    receiveDatatThread.launch();
    sendDatatThread.launch();

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        player->update(&window);
        view.setCenter(player->getPosition());
        window.setView(view);

        window.draw(map);
        window.draw(*player);
        drawEnnemis();
        drawWeapons();

        window.display();
        window.clear(sf::Color::White);

        checkCollision();
        manageBullets();
    }
}

void Game::checkCollision()
{
    for(unsigned int i=0; i < map.getVecTree().size(); i++)
    {
        if(Collision::PixelPerfectTest(player->getSprite(), map.getVecTree()[i]->getSprite()))
            player->setPosition(player->getExPos());
    }

    for(unsigned int i=0; i < map.getVecWeapon().size(); i++)
    {
        if(player->getSprite().getGlobalBounds().intersects(map.getVecWeapon()[i]->getSprite().getGlobalBounds())
           && map.getVecWeapon()[i] != player->getCurrentWeapon())
        {
            map.getVecWeapon()[i]->drawInfo(true);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                if(player->hasWeapon())
                {
                    player->dropWeapon();
                }
                player->attach(map.getVecWeapon()[i]);
            }
        }
        else
        {
            map.getVecWeapon()[i]->drawInfo(false);
        }
    }

    for(unsigned int i = 0; i < map.getVecTree().size(); i++)
    {
        for(unsigned int j = 0; j < map.getVecWeapon().size(); j++)
        {
            for(unsigned int k = 0; k < map.getVecWeapon()[j]->getVecBullets().size(); k++)
            {
                if(Collision::PixelPerfectTest(*map.getVecWeapon()[j]->getVecBullets()[k], map.getVecTree()[i]->getSprite()))
                {
                    map.getVecTree()[i]->substractLife(map.getVecWeapon()[j]->getDammage());
                    map.getVecWeapon()[j]->destroyBullets(k);
                    if(map.getVecTree()[i]->getLife() <= 0)
                    {
                        map.destroyTree(i);
                    }
                }
            }
        }
    }
}

void Game::manageBullets()
{
    player->getExWeapon()->update();
}

void Game::receiveData()
{
    if(!receiveThreadStarted)
    {
        receiveThreadStarted = true;

        if (receiveUdp.bind(PORT) != sf::Socket::Done)
        {
            std::cout << "Impossible to read port : " << PORT << std::endl;
        }
        else
        {
            std::cout << "Listen on port : " << PORT << std::endl;

            while(window.isOpen())
            {
                std::size_t received;
                sf::IpAddress sender;
                unsigned short port;

                if (receiveUdp.receive(receivePacket, sender, port) != sf::Socket::Done)
                {
                    std::cout << "Can't receive packet" << std::endl;
                }

                float x;
                float y;
                float angle;
                std::string senderIp;
                bool ennemiExist = false;
                int nb;
                int weaponID;
                receivePacket >> x >> y >> angle >> senderIp >> weaponID;

                std::cout << "Packet received : " << x << " ; " << y << " : " << angle << " from : " << senderIp << std::endl;

                for(unsigned int i = 0; i < vecEnnemi.size(); i++)
                {
                    if(vecEnnemi[i]->getIp() == senderIp)
                    {
                         ennemiExist = true;
                         nb = i;
                    }
                }
                if(!ennemiExist)
                {
                    vecEnnemi.push_back(new Ennemi(sf::Vector2f(x, y), angle, senderIp));
                    attributeWeapon(weaponID, vecEnnemi.size());
                }
                else
                {
                    vecEnnemi[nb]->setPosition(sf::Vector2f(x, y));
                    vecEnnemi[nb]->setRotation(angle);
                    attributeWeapon(weaponID, nb);
                }

                sf::sleep(sf::seconds(SEND_INTERVAL));
                receivePacket.clear();
            }
        }
    }
}

void Game::sendData()
{
    if(!sendThreadStarted)
    {
        sendThreadStarted = true;

        while(window.isOpen())
        {
            sendPacket << player->getPosition().x << player->getPosition().y << player->getSprite().getRotation() << ip.toString();

            if (sendUdp.send(sendPacket, receiver, PORT) != sf::Socket::Done)
            {
                std::cout << "Can't send packet" << std::endl;
            }

            sendPacket.clear();
            sf::sleep(sf::seconds(SEND_INTERVAL));
        }
    }
}

void Game::drawEnnemis()
{
    for(unsigned int i = 0; i < vecEnnemi.size(); i++)
    {
        window.draw(*vecEnnemi[i]);
        vecEnnemi[i]->update();
    }
}

void Game::drawWeapons()
{
    for(unsigned int i = 0; i < map.getVecWeapon().size(); i++)
    {
        window.draw(*map.getVecWeapon()[i]);
    }
}

void Game::setAddressIP(std::string ip)
{
    receiver = ip;
}

void Game::attributeWeapon(int id, int i)
{
    switch(id)
    {
        case 1:
            vecEnnemi[i]->setWeapon(Sniper());
            break;
        case 2:
            vecEnnemi[i]->setWeapon(AK());
            break;
    }
}
