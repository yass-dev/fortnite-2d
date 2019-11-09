#include "Tree.h"

Tree::Tree()
    : life(100)
{
    texture.loadFromFile("tree.png");
    texture.setSmooth(true);

    sprite.setTexture(texture);
}

void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}

sf::Sprite Tree::getSprite() const
{
    return sprite;
}

void Tree::setPosition(sf::Vector2f coord)
{
    sprite.setPosition(coord);
}

sf::Vector2f Tree::getPosition() const
{
    return sprite.getPosition();
}

void Tree::substractLife(int nb)
{
    life -= nb;
    std::cout << "life : " << life << std::endl;
}

int Tree::getLife() const
{
    return life;
}
