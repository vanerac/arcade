/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SpriteSFML
*/

#include "LibSFML.hpp"

SpriteSFML::SpriteSFML()
{
    _sprite.setTexture(_texture);
}

SpriteSFML::SpriteSFML(const std::string &spritePath, arcade::data::Vector2f scale)
{
    setSprite(spritePath, {});
    _sprite.setTexture(_texture);
    setScale(scale);
}

SpriteSFML::~SpriteSFML()
{
}

sf::Sprite &SpriteSFML::getSprite()
{
    return _sprite;
}

void SpriteSFML::setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
    (void)asciiSprite;
    _texture.loadFromFile(spritePath);
}

void SpriteSFML::setPosition(arcade::data::Vector2f pos)
{
    _sprite.setPosition(sf::Vector2f{pos.x, pos.y});
}

arcade::data::Vector2f SpriteSFML::getPosition() const
{
    auto pos = _sprite.getPosition();
    return arcade::data::Vector2f{pos.x, pos.y};
}

void SpriteSFML::move(arcade::data::Vector2f pos)
{
    _sprite.move(sf::Vector2f{pos.x, pos.y});
}

void SpriteSFML::move(float x, float y)
{
    _sprite.move(sf::Vector2f{x, y});
}

void SpriteSFML::setOrigin(arcade::data::Vector2f origin)
{
    _sprite.setOrigin(sf::Vector2f{origin.x, origin.y});
}

arcade::data::Vector2f SpriteSFML::getOrigin()
{
    auto origin = _sprite.getOrigin();
    return arcade::data::Vector2f{origin.x, origin.y};
}

arcade::data::FloatRect SpriteSFML::getLocalBounds()
{
    auto b = _sprite.getLocalBounds();
    return arcade::data::FloatRect{b.left, b.top, b.width, b.height};
}

void SpriteSFML::setScale(arcade::data::Vector2f scale)
{
    _sprite.setScale(scale.x, scale.y);
}

arcade::data::Vector2f SpriteSFML::getScale()
{
    auto scale = _sprite.getScale();
    return arcade::data::Vector2f{scale.x, scale.y};
}

float SpriteSFML::getRotation()
{
    return _sprite.getRotation();
}

void SpriteSFML::setRotation(float angle)
{
    _sprite.setRotation(angle);
}

void SpriteSFML::rotate(float angle)
{
    _sprite.rotate(angle);
}

void SpriteSFML::setTextureRect(const arcade::data::IntRect &rect)
{
    _sprite.setTextureRect(sf::IntRect{rect.left, rect.top, rect.width, rect.height});
}

arcade::data::IntRect SpriteSFML::getTextureRect() const
{
    auto rect = _sprite.getTextureRect();
    return arcade::data::IntRect{rect.top, rect.left, rect.width, rect.height};
}

void SpriteSFML::setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors)
{
    (void)asciiColors;
    _sprite.setColor(sf::Color{color.r, color.g, color.b, color.a});
}