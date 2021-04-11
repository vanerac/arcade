/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** TextSFML
*/

#include "LibSFML.hpp"
#include "Errors.hpp"

TextSFML::TextSFML()
{
}

TextSFML::TextSFML(const std::string &text)
{
    _text.setString(text);
}

TextSFML::~TextSFML()
{
}

void TextSFML::setText(const std::string &text)
{
    _text.setString(text);
}

std::string TextSFML::getText() const
{
    return _text.getString();
}

void TextSFML::setPosition(arcade::data::Vector2f pos)
{
    _text.setPosition(sf::Vector2f{pos.x, pos.y});
}

arcade::data::Vector2f TextSFML::getPosition() const
{
    auto pos = _text.getPosition();
    return arcade::data::Vector2f{pos.x, pos.y};
}

void TextSFML::setFont(const std::string &fontPath)
{
    if (!_font.loadFromFile(fontPath)) {
        throw arcade::errors::Error("Failed to load font '" + fontPath + "'.");
    }
    _text.setFont(_font);
}

void TextSFML::setColor(arcade::data::Color color)
{
    _text.setFillColor(sf::Color{color.r, color.g, color.b, color.a});
}

arcade::data::Color TextSFML::getColor() const
{
    auto color = _text.getFillColor();
    return arcade::data::Color{color.r, color.g, color.b, color.a};
}

void TextSFML::setCharacterSize(unsigned int size)
{
    _text.setCharacterSize(size);
}

arcade::data::FloatRect TextSFML::getLocalBounds() const
{
    auto rect = _text.getLocalBounds();
    return arcade::data::FloatRect{rect.top, rect.left, rect.width, rect.height};
}

arcade::data::FloatRect TextSFML::getGlobalBounds() const
{
    auto rect = _text.getGlobalBounds();
    return arcade::data::FloatRect{rect.top, rect.left, rect.width, rect.height};
}

void TextSFML::setOrigin(arcade::data::Vector2f origin)
{
    _text.setOrigin(sf::Vector2f{origin.x, origin.y});
}

arcade::data::Vector2f TextSFML::getOrigin() const
{
    auto org = _text.getOrigin();
    return arcade::data::Vector2f{org.x, org.y};
}

sf::Text &TextSFML::getsfText()
{
    return _text;
}