#ifndef INFORECTANGLE_H
#define INFORECTANGLE_H

#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"

class InfoRectangle : public sf::Drawable
{
    public:
        InfoRectangle();

        void setSize(sf::Vector2f size);
        void setPosition(sf::Vector2f pos);
        void setText(std::string str);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::RectangleShape rect;
        sf::RectangleShape rectKey;
        sf::Text text;
        sf::Text textKey;
        sf::Font font;

        std::string name;
};

#endif // INFORECTANGLE_H
