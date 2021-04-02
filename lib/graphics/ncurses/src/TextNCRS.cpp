/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** TextNCRS
*/

#include "LibNCRS.hpp"

TextNCRS::TextNCRS()
{
}

TextNCRS::TextNCRS(const std::string &text)
{
    _text = text;
}

TextNCRS::~TextNCRS()
{
}

void TextNCRS::setText(const std::string &text)
{
    _text = text;
}

std::string TextNCRS::getText() const
{
    return _text;
}

void TextNCRS::setPosition(arcade::data::Vector2f pos)
{
    _pos = pos;
}

arcade::data::Vector2f TextNCRS::getPosition() const
{
    return _pos;
}

void TextNCRS::setFont(const std::string &fontPath)
{
    (void)fontPath;
}

void TextNCRS::setColor(arcade::data::Color color)
{
    auto pair = LibNCRS::colorToNcrsColor(color);
    _color = pair.first;
    _ncrsColor = pair.second;
}

arcade::data::Color TextNCRS::getColor() const
{
    return _color;
}

unsigned int TextNCRS::getNcrsColor() const
{
    return _ncrsColor;
}

void TextNCRS::setCharacterSize(unsigned int size)
{
    (void)size;
}

const char *TextNCRS::getString() const
{
    return _text.data();
}

arcade::data::FloatRect TextNCRS::getLocalBounds()
{
    return arcade::data::FloatRect{_pos.y, _pos.x, static_cast<float>(_text.size()), 1.0f};
}

void TextNCRS::setOrigin(arcade::data::Vector2f origin)
{
    _origin = origin;
}

arcade::data::Vector2f TextNCRS::getOrigin()
{
    return _origin;
}