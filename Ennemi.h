#ifndef ENNEMI_H
#define ENNEMI_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"

class Ennemi : public sf::Drawable
{
    public:
        Ennemi();
        Ennemi(sf::Vector2f pos, float angle, std::string ipAddr);

        void setPosition(sf::Vector2f pos);
        void setRotation(float angle);
        void setWeapon(Weapon w);
        void update();

        sf::Vector2f getPosition() const;

        Weapon getWeapon() const;

        std::string getIp() const;

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        sf::Sprite sprite;
        sf::Texture texture;

        int playerSize;
        int life;

        Weapon weapon;

        std::string ip;
};

#endif // ENNEMI_H
