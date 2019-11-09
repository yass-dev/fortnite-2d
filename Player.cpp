#include "player.h"

Player::Player()
    : anim(1, Down), playerSize(45), speed(4), canMove(true), isJumping(false), aimLine(sf::Vector2f(150.f, 5.f)), hasWeapons(false)
{
    texture.loadFromFile("sprite.png");
    texture.setSmooth(true);

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(anim.x * playerSize, anim.y * playerSize, playerSize, playerSize));
    sprite.setOrigin(sprite.getPosition().x  + playerSize/2, sprite.getPosition().y + playerSize/2);

    aimLine.setFillColor(sf::Color::Red);

    window = new sf::Window();
    exWeapon = new Weapon();
    weapon = nullptr;
}

void Player::update(sf::Window *w)
{
    window = w;
    gestionClavier();
    gestionSprite();
    gestionFPS();

    float AB = sprite.getPosition().x - sf::Mouse::getPosition(*window).x;
    float AC = sprite.getPosition().y - sf::Mouse::getPosition(*window).y;
    float longueur = sqrt(std::pow(AB, 2) + std::pow(AC, 2));

    aimLine.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
    aimLine.setRotation(sprite.getRotation() + 90);
    aimLine.setSize(sf::Vector2f(longueur, 1.f));

    float angle = atan2f(AC, AB);
    float angleD = angle * 180/M_PI;

    if(hasWeapons)
    {
        weapon->setPosition(sprite.getPosition());
        weapon->setRotation(sprite.getRotation());
        weapon->update();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            dropWeapon();
        }
    }
}

void Player::gestionClavier()
{
    if(canMove)
    {
        exPos = sprite.getPosition();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            updateFPS = true;
            anim.y = Up;
            sprite.move(0, -speed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            updateFPS = true;
            anim.y = Down;
            sprite.move(0, speed);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            updateFPS = true;
            anim.y = Right;
            sprite.move(speed, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            updateFPS = true;
            anim.y = Left;
            sprite.move(-speed, 0);
        }
        else
        {
            updateFPS = false;
        }

        float o = sf::Mouse::getPosition(*window).y - (sprite.getPosition().y);
        float adj = sf::Mouse::getPosition(*window).x - (sprite.getPosition().x);

        float angle = atan2f(o, adj);
        float angleD = angle * 180/M_PI;
        sprite.setRotation(angleD - 90);
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && weapon != nullptr)
    {
        weapon->shoot();
    }
}

void Player::gestionSprite()
{
    sprite.setTextureRect(sf::IntRect(anim.x * playerSize, anim.y * playerSize, playerSize, playerSize));
}

void Player::gestionFPS()
{
    if(updateFPS)
    {
        if(Time.getElapsedTime().asMilliseconds() >= 50)
        {
            anim.x--;
            if(anim.x * playerSize >= texture.getSize().x)
            {
                anim.x = 2;
            }
            Time.restart();
        }
    }
}

void Player::setSpeed(int speeds)
{
    speed = speeds;
}

void Player::setCanMove(bool can)
{
    canMove = can;
}

sf::Vector2f Player::getExPos() const
{
    return exPos;
}

int Player::getDirection() const
{
    return anim.y;
}

int Player::getSize() const
{
    return playerSize;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
    if(hasWeapons)
        target.draw(aimLine);
}

void Player::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Player::setPosition(int x, int y)
{
    sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

sf::Sprite Player::getSprite() const
{
    return sprite;
}

int Player::getSpeed() const
{
    return speed;
}

void Player::attach(Weapon *w)
{
    if(takeWeaponClock.getElapsedTime().asMilliseconds() >= 500)
    {
        std::cout << "Elapsed time : " << takeWeaponClock.getElapsedTime().asMilliseconds() << std::endl;
        weapon = w;
        hasWeapons = true;
        weapon->setAttached(true);
        takeWeaponClock.restart();
    }
}

Weapon *Player::getCurrentWeapon() const
{
    return weapon;
}

void Player::dropWeapon()
{
    weapon->setRotation(0.f);
    weapon->setAttached(false);
    hasWeapons = false;
    exWeapon = weapon;
    weapon = nullptr;
}

bool Player::hasWeapon() const
{
    return hasWeapons;
}

Weapon *Player::getExWeapon() const
{
    return exWeapon;
}
