#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <algorithm>

#include "Player.h"
#include "Tree.h"
#include "map.h"
#include "Collision.hpp"
#include "Sniper.h"
#include "Ennemi.h"

#define SEND_INTERVAL 0.01
#define PORT 80804

class Game
{
public:
    Game(sf::Vector2i screenSize);

    void run();

    void receiveData();
    void sendData();
    void setAddressIP(std::string ip);

private:
    void checkCollision();
    void manageBullets();
    void drawEnnemis();
    void drawWeapons();
    void attributeWeapon(int id, int i);

    sf::RenderWindow window;
    sf::View view;

    sf::Thread receiveDatatThread;
    sf::Thread sendDatatThread;
    sf::Mutex mutex;

    sf::UdpSocket sendUdp;
    sf::UdpSocket receiveUdp;

    sf::Packet receivePacket;
    sf::Packet sendPacket;

    sf::Vector2f *playerPos;

    sf::IpAddress ip;

    Player *player;
    Map map;
    Weapon *exWeapon;

    bool sendThreadStarted;
    bool receiveThreadStarted;

    std::vector<Ennemi*> vecEnnemi;

    std::string receiver;
};

#endif // GAME_H
