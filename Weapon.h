#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <time.h>

#include "InfoRectangle.h"

#define PI 3.14159265

class Weapon : public sf::Drawable
{
public:
    Weapon(std::string fileName);
    Weapon();

    void substractAmmo(int nb);
    void addAmmo(int nb);
    void setAttached(bool on);
    void setPosition(sf::Vector2f pos);
    void setRotation(float angle);
    void shoot();
    void update();
    void drawInfo(bool on);
    void destroyBullets(int i);

    sf::Sprite getSprite() const;

    int getCurrentAmmo() const;
    int getDammage() const;
    int getId() const;

    bool canShoot() const;
    bool isAttached() const;

    std::vector<sf::Sprite*> getVecBullets() const;
    std::string getName() const;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture textureAmmo;
    sf::Clock reloadClock;
    sf::Clock shootClock;

    bool isAttach;
    bool canDrawInfo;

    int currentAmmo;
    int chargerSize;
    int chargerNb;
    int degat;
    int scope;
    int bulletSpeed;
    int precision;
    int id;

    float reloadTime;
    float timeBetweenShoot;

    std::string name;

    std::vector<sf::Sprite*> vecSpriteBullets;

    InfoRectangle infoRectangle;

private:
    int getRandomInt();

};

#endif // WEAPON_H
