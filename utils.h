#include "weapons.h"
#include <SFML/Graphics.hpp>

sf::Packet& operator <<(sf::Packet& packet, const Weapon &weapon)
{
    return packet << weapon.sprite << weapon.texture;
}

sf::Packet& operator >>sf::Packet& packet, const Weapon &weapon)
{
    return packet >> weapon.sprite >> weapon.texture;
}
