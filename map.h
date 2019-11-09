#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <utility>

#include "Tree.h"
#include "Sniper.h"
#include "AK.h"

#define MAP_SIZE 50

class Map : public sf::Drawable
{
public:
    Map();

    void load(std::string fileName);
    void destroyTree(int i);

    std::vector<Tree*> getVecTree() const;
    std::vector<Weapon*> getVecWeapon() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<std::string> explode(std::string s, char delim);

    std::vector<Tree*> vecTree;
    std::vector<Weapon*> vecWeapon;
    std::vector<sf::Sprite*> vecSpriteSol;
    unsigned int mapHeight;
    unsigned int mapWidth;
    sf::Texture texture;
    bool hasDrawedFloor;
};

#endif // MAP_H
