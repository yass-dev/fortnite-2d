#include "InfoRectangle.h"

InfoRectangle::InfoRectangle()
{
    rect.setFillColor(sf::Color(31, 31, 31, 89.25));
    rect.setSize(sf::Vector2f(150, 40));

    font.loadFromFile("font/coolvetica rg.ttf");

    text.setString(name);
    text.setCharacterSize(13);
    text.setFillColor(sf::Color::White);
    text.setFont(font);

    textKey.setString("E");
    textKey.setCharacterSize(15);
    textKey.setFillColor(sf::Color::White);
    textKey.setFont(font);

    rectKey.setFillColor(sf::Color(31, 31, 31, 89.25));
    rectKey.setSize(sf::Vector2f(20, 40));
}

void InfoRectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rect);
    target.draw(text);
    target.draw(rectKey);
    target.draw(textKey);
}

void InfoRectangle::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos.x - 50, pos.y + 40);
    text.setPosition(pos.x - 45, pos.y + 45);
    rectKey.setPosition(rect.getPosition().x + rect.getSize().x + 10, rect.getPosition().y);
    textKey.setPosition(rectKey.getPosition().x + 5, rectKey.getPosition().y + 10);
}

void InfoRectangle::setSize(sf::Vector2f size)
{
    rect.setSize(size);
}

void InfoRectangle::setText(std::string str)
{
    text.setString(str);
}
