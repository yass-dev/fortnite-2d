#include "Ennemi.h"

Ennemi::Ennemi()
    : playerSize(40)
{
    texture.loadFromFile("sprite-ennemi.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(20, 20);
}

Ennemi::Ennemi(sf::Vector2f pos, float angle, std::string ipAddr)
    : playerSize(40)
{
    texture.loadFromFile("sprite-ennemi.png");
    texture.setSmooth(true);
    sprite.setOrigin(sprite.getPosition().x  + playerSize/2, sprite.getPosition().y + playerSize/2);
    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setRotation(angle);
    ip = ipAddr;
}

void Ennemi::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
    target.draw(weapon);
}

void Ennemi::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Ennemi::setRotation(float angle)
{
    sprite.setRotation(angle);
}

Weapon Ennemi::getWeapon() const
{
    return weapon;
}

void Ennemi::setWeapon(Weapon w)
{
    weapon = w;
}

std::string Ennemi::getIp() const
{
    return ip;
}

sf::Vector2f Ennemi::getPosition() const
{
    return sprite.getPosition();
}

void Ennemi::update()
{
    weapon.setPosition(sprite.getPosition());
    weapon.setRotation(sprite.getRotation());
}
