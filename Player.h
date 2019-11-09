#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>

#include "Weapon.h"

class Player : public sf::Drawable
{

public:
    Player();

    void update(sf::Window *window);
    void setPosition(sf::Vector2f pos);
    void setPosition(int x, int y);
    void setSpeed(int speeds);
    void setCanMove(bool can);
    void attach(Weapon *w);
    void dropWeapon();

    sf::Vector2f getExPos() const;
    sf::Vector2f getPosition() const;
    sf::Sprite getSprite() const;

    int getDirection() const;
    int getSize() const;
    int getSpeed() const;

    Weapon *getCurrentWeapon() const;
    Weapon *getExWeapon() const;

    bool hasWeapon() const;

    enum Dir{Down, Left, Right, Up};

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void gestionClavier();
    void gestionSprite();
    void gestionFPS();
    void gestionSaut(int t);

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock Time;
    sf::Vector2i anim;
    sf::Window *window;
    sf::RectangleShape aimLine;
    sf::Clock takeWeaponClock;

    bool updateFPS = true;
    bool canMove;
    bool isJumping;
    bool hasWeapons;

    const int playerSize;
    int speed = 10;
    int life;

    sf::Vector2f exPos;

    Weapon *weapon;
    Weapon *exWeapon;
};

#endif // PLAYER_H
