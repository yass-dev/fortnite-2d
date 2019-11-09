#include "Weapon.h"

Weapon::Weapon(std::string fileName)
    : canDrawInfo(false)
{
    texture.loadFromFile(fileName);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    textureAmmo.loadFromFile(fileName.insert(fileName.size() - 4, "-ammo"));
    textureAmmo.setSmooth(true);

    srand(time(NULL));
}

Weapon::Weapon()
    : canDrawInfo(false)
{
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(canDrawInfo)
    {
        target.draw(infoRectangle);
    }
    target.draw(sprite);

    for(unsigned int i=0; i < vecSpriteBullets.size(); i++)
    {
        target.draw(*vecSpriteBullets[i]);
    }
}

void Weapon::setAttached(bool on)
{
    isAttach = on;
}

void Weapon::substractAmmo(int nb)
{
    currentAmmo -= nb;
}

void Weapon::addAmmo(int nb)
{
    currentAmmo += nb;
}


void Weapon::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

int Weapon::getCurrentAmmo() const
{
    return currentAmmo;
}

sf::Sprite Weapon::getSprite() const
{
    return sprite;
}

void Weapon::setRotation(float angle)
{
    sprite.setRotation(angle);
}

bool Weapon::canShoot() const
{
    if(reloadClock.getElapsedTime().asSeconds() >= reloadTime && shootClock.getElapsedTime().asMilliseconds() >= timeBetweenShoot)
        return true;
    else
        return false;
}
void Weapon::shoot()
{
    if(canShoot() && currentAmmo > 0)
    {
        vecSpriteBullets.push_back(new sf::Sprite);
        vecSpriteBullets.back()->setTexture(textureAmmo);
        vecSpriteBullets.back()->setPosition(sprite.getPosition());
        vecSpriteBullets.back()->setRotation(sprite.getRotation() + getRandomInt() - precision);
        shootClock.restart();
        currentAmmo--;
        std::cout << "Shoot !" << std::endl;
    }
    else
    {
        if(currentAmmo <= 0)
        {
            if(chargerNb > 0)
            {
                reloadClock.restart();
                currentAmmo = chargerSize;
                chargerNb --;
                std::cout << "Reload !" << std::endl;
            }
            else
            {
                std::cout << "No ammo" << std::endl;
            }
        }
    }
}

std::vector<sf::Sprite*> Weapon::getVecBullets() const
{
    return vecSpriteBullets;
}

bool Weapon::isAttached() const
{
    return isAttach;
}

void Weapon::update()
{
    for(unsigned int i=0; i < vecSpriteBullets.size(); i++)
    {
        float x = std::cos((vecSpriteBullets[i]->getRotation() + 90) * PI/180) * bulletSpeed;
        float y = std::sin((vecSpriteBullets[i]->getRotation() + 90) * PI/180) * bulletSpeed;

        vecSpriteBullets[i]->move(x, y);
    }
}

int Weapon::getRandomInt()
{
    if(precision != 0)
        return rand()%(precision - (-precision)) + precision;
    else
        return 0;
}

void Weapon::drawInfo(bool on)
{
    canDrawInfo = on;
    infoRectangle.setPosition(sprite.getPosition());
}

std::string Weapon::getName() const
{
    return name;
}

int Weapon::getDammage() const
{
    return degat;
}

void Weapon::destroyBullets(int i)
{
    vecSpriteBullets.erase(vecSpriteBullets.begin() + i);
}

int Weapon::getId() const
{
    return id;
}
