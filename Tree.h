#ifndef TREE_H
#define TREE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Tree : public sf::Drawable
{
public:
    Tree();

    void setPosition(sf::Vector2f coord);
    void substractLife(int nb);

    sf::Vector2f getPosition() const;
    sf::Sprite getSprite() const;

    int getLife() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite sprite;
    sf::Texture texture;

    int life;

};

#endif // TREE_H
