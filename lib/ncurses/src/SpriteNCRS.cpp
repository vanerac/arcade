/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SpriteNCRS
*/

#include "LibNCRS.hpp"

SpriteNCRS::SpriteNCRS()
{
}

SpriteNCRS::SpriteNCRS(const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
{
    setSprite("", asciiSprite);
    setScale(scale);
}

SpriteNCRS::~SpriteNCRS()
{
}

void SpriteNCRS::setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
    (void)spritePath;
    _originalSprite.clear();
    _originalSprite.reserve(asciiSprite.size());
    int y = 0;
    for (auto &line : asciiSprite) {
        int x = 0;
        _originalSprite.emplace_back(line.size());
        for (auto c : line) {
            _originalSprite[y][x++] = c;
        }
        ++y;
    }
    _sprite = _originalSprite;
}

void SpriteNCRS::setPosition(arcade::data::Vector2f pos)
{
    _pos = pos;
}

arcade::data::Vector2f SpriteNCRS::getPosition() const
{
    return _pos;
}

void SpriteNCRS::move(arcade::data::Vector2f pos)
{
    _pos += pos;
}

void SpriteNCRS::setOrigin(arcade::data::Vector2f origin)
{
    _origin = origin;
}

arcade::data::Vector2f SpriteNCRS::getOrigin()
{
    return _origin;
}

arcade::data::FloatRect SpriteNCRS::getLocalBounds()
{
    int maxWidth = 0;
    for (auto &line : _sprite) {
        int sz = line.size();
        maxWidth = sz > maxWidth ? sz : maxWidth;
    }
    return arcade::data::FloatRect{_pos.x, _pos.y, maxWidth, static_cast<int>(_sprite.size())};
}

void SpriteNCRS::setScale(arcade::data::Vector2f scale) // TODO
{
    if (_scale == scale) {
        return;
    }
    _scale = scale;
}

arcade::data::Vector2f SpriteNCRS::getScale()
{
    return _scale;
}

float SpriteNCRS::getRotation()
{
    return _rotation;
}

void SpriteNCRS::setRotation(float angle) // TODO
{
    _rotation = angle;
}

void SpriteNCRS::rotate(float angle)
{
    setRotation(getRotation() + angle);
}

void SpriteNCRS::setTextureRect(const arcade::data::IntRect &rect) // TODO
{
    _textureRect = rect;
}

void SpriteNCRS::setColor(arcade::data::Color globalColor, const std::vector<std::vector<arcade::data::Color>> &colors)
{
    (void)globalColor;
    int y = 0;
    for (auto &line : colors) {
        int x = 0;
        for (auto &c : line) {
            _originalSprite[y][x] |= COLOR_PAIR(LibNCRS::getNcrsColorPair(LibNCRS::colorToNcrsColor(c).second, COLOR_BLACK));
        }
        ++y;
    }
    _sprite = _originalSprite;
    auto tmpScale = _scale;
    _scale.x = 1;
    _scale.y = 1;
    setScale(tmpScale);
    auto tmpRotation = _rotation;
    _rotation = 0;
    setRotation(tmpRotation);
    auto tmpTextureRect = _textureRect;
    auto b = getLocalBounds();
    _textureRect.top = 0;
    _textureRect.left = 0;
    _textureRect.width = b.width;
    _textureRect.height = b.height;
    setTextureRect(tmpTextureRect);
}

std::vector<std::vector<chtype>> &SpriteNCRS::getSprite()
{
    return _sprite;
}