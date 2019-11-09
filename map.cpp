#include "map.h"

Map::Map()
{
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("sol.png");

    for(unsigned int i= 0; i < MAP_SIZE + 20; i++)
    {
        for(unsigned int j= 0; j < MAP_SIZE; j++)
        {
            vecSpriteSol.push_back(new sf::Sprite(*texture));
            vecSpriteSol.back()->setPosition(i*20, j*20);
        }
    }
}

void Map::load(std::string fileName)
{
    std::ifstream file(fileName, std::ios::in);
    std::string tmp;

    if(!file)
        std::cout << "Fichier non trouve" << std::endl;

    while(std::getline(file, tmp))
    {
        if(tmp[0] == 'T')
        {
            vecTree.push_back(new Tree());
            std::string coord = tmp.substr(2, tmp.size()-1);
            std::cout << coord << std::endl;
            float x = stof(explode(coord, ';')[0]);
            float y = stof(explode(coord, ';')[1]);
            vecTree.back()->setPosition(sf::Vector2f(x, y));
        }
        else if(tmp[0] == 'W')
        {
            if(tmp[1] == 'S')
            {
                vecWeapon.push_back(new Sniper);
                std::string coord = tmp.substr(3, tmp.size()-1);
                std::cout << "Coord of sniper : " << coord << std::endl;
                float x = stof(explode(coord, ';')[0]);
                float y = stof(explode(coord, ';')[1]);
                vecWeapon.back()->setPosition(sf::Vector2f(x, y));
            }
            else if(tmp[1] == 'A' && tmp[2] == 'K')
            {
                vecWeapon.push_back(new AK);
                std::string coord = tmp.substr(4, tmp.size()-1);
                std::cout << "Coord of AK : " << coord << std::endl;
                float x = stof(explode(coord, ';')[0]);
                float y = stof(explode(coord, ';')[1]);
                vecWeapon.back()->setPosition(sf::Vector2f(x, y));
            }
        }
    }

    file.close();

    std::cout << vecTree.size() << " tree" <<std::endl;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(unsigned int i=0; i < vecSpriteSol.size(); i++)
    {
        target.draw(*vecSpriteSol[i]);
    }
    for(unsigned int i=0; i < vecTree.size(); i++)
    {
        target.draw(*vecTree[i]);
    }
}

std::vector<std::string> Map::explode(std::string s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

std::vector<Tree*> Map::getVecTree() const
{
    return vecTree;
}

std::vector<Weapon*> Map::getVecWeapon() const
{
    return vecWeapon;
}

void Map::destroyTree(int i)
{
    vecTree.erase(vecTree.begin() + i);
}
