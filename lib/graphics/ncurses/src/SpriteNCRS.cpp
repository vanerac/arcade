/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SpriteNCRS
*/
#include <iostream>

#include <cmath>
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
    if (asciiSprite.size()) {
        _originalSprite.reserve(asciiSprite.size());
        int y = 0;
        int width = asciiSprite[0].size();
        for (auto &line : asciiSprite) {
            int x = 0;
            _originalSprite.emplace_back(width);
            for (auto c : line) {
                if (x >= width) {
                    break;
                }
                _originalSprite[y][x++] = c;
            }
            ++y;
        }
    }
    _sprite = _originalSprite;
    _textureRect.top = 0;
    _textureRect.left = 0;
    _textureRect.width = _sprite.size() ? _sprite[0].size() : 0;
    _textureRect.height = _sprite.size();
    // endwin();
    // std::cout << "[" << _textureRect.width << ", " << _textureRect.height << "]" << std::endl;
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

void SpriteNCRS::move(float x, float y)
{
    _pos.x += x;
    _pos.y += y;
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
    return arcade::data::FloatRect{_pos.x, _pos.y, static_cast<float>(_textureRect.width), static_cast<float>(_textureRect.height)};
}

void SpriteNCRS::setScale(arcade::data::Vector2f scale) // TODO: (change also rect)
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

void SpriteNCRS::setRotation(float angle)
{
    float rot = angle - (360 * static_cast<int>(angle / 360));
    rot = rot >= 0 ? rot : 360 + rot;
    rot = std::round(rot / 90.0f) * 90;
    rot = rot == 360 ? 0 : rot;
    _rotation = angle;
    if (rot == _actualRotation) {
        return;
    }
    int timesToDo = (rot - _actualRotation) / 90;
    timesToDo = timesToDo < 0 ? 4 + timesToDo : timesToDo;
    for (short i = 0; i < timesToDo; ++i) {
        auto b = getLocalBounds();
        arcade::data::Vector2u size{static_cast<unsigned int>(b.width), static_cast<unsigned int>(b.height)};
        std::vector<std::vector<chtype>> res;
        res.reserve(size.x);
        for (unsigned int y = 0; y < size.x; ++y) {
            res.emplace_back(size.y);
            for (unsigned int x = 0; x < size.y; ++x) {
                res[y][x] = _sprite[size.y - x - 1][y];
            }
        }
        _sprite = res;
        _textureRect.width = size.y;
        _textureRect.height = size.x;
    }
    _actualRotation = rot;
}

void SpriteNCRS::rotate(float angle)
{
    setRotation(getRotation() + angle);
}

void SpriteNCRS::setTextureRect(const arcade::data::IntRect &rect)
{
    _textureRect = rect;
}

arcade::data::IntRect SpriteNCRS::getTextureRect() const
{
    return _textureRect;
}

void SpriteNCRS::setColor(arcade::data::Color globalColor, const std::vector<std::vector<arcade::data::Color>> &colors)
{
    (void)globalColor;
    for (unsigned int y = 0; y < _originalSprite.size() && y < colors.size(); ++y) {
        for (unsigned int x = 0; x  < _originalSprite[y].size() && colors[y].size(); ++x) {
            _originalSprite[y][x] |= COLOR_PAIR(LibNCRS::getNcrsColorPair(LibNCRS::colorToNcrsColor(colors[y][x]).second, COLOR_BLACK));
        }
    }
    _sprite = _originalSprite;
    auto tmpScale = _scale;
    _scale.x = 1;
    _scale.y = 1;
    setScale(tmpScale);
    auto tmpRotation = _rotation;
    _rotation = 0;
    setRotation(tmpRotation);
}

std::vector<std::vector<chtype>> &SpriteNCRS::getSprite()
{
    return _sprite;
}