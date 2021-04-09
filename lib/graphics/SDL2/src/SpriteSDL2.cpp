/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SpriteSDL2
*/

#include "LibSDL2.hpp"
#include "Errors.hpp"

SpriteSDL2::SpriteSDL2()
{
}

SpriteSDL2::SpriteSDL2(const std::string &spritePath, arcade::data::Vector2f scale)
{
    setSprite(spritePath, {});
    setScale(scale);
}

SpriteSDL2::~SpriteSDL2()
{
}

void SpriteSDL2::setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
    (void)asciiSprite;
    if (!LibSDL2::renderer) {
        throw arcade::errors::Error("[SDL2::setSprite(" + spritePath + ", ...)]: No renderer were set.");
    }
    auto surface = make_surface(SDL_LoadBMP(spritePath.c_str()));
    if (!surface || !(_sprite = make_texture(SDL_CreateTextureFromSurface(LibSDL2::renderer.get(), surface.get())))) {
        throw arcade::errors::Error("Failed to load sprite '" + spritePath + "': " + SDL_GetError());
    }
    auto r = surface->clip_rect;
    _texture.width = r.w;
    _texture.height = r.h;
    _originalSize.x = r.w;
    _originalSize.y = r.h;
    _displayRect.x = r.w;
    _displayRect.y = r.h;
    _scale = {1, 1};
}

void SpriteSDL2::draw()
{
    SDL_Rect texture;
    texture.x = _texture.left;
    texture.y = _texture.top;
    texture.w = _texture.width;
    texture.h = _texture.height;
    SDL_Rect rect;
    rect.x = _pos.x;
    rect.y = _pos.y;
    rect.w = _displayRect.x;
    rect.h = _displayRect.y;
    if (_sprite && SDL_RenderCopy(LibSDL2::renderer.get(), _sprite.get(), &texture, &rect) < 0) {
        throw arcade::errors::Error(std::string{"Unexpected error while drawing a sprite: "} + SDL_GetError());
    }
}

void SpriteSDL2::setPosition(arcade::data::Vector2f pos)
{
    _pos.x = pos.x - _origin.x;
    _pos.y = pos.y - _origin.y;
}

arcade::data::Vector2f SpriteSDL2::getPosition() const
{
    return {_pos.x + _origin.x, _pos.y + _origin.y};
}

void SpriteSDL2::move(arcade::data::Vector2f pos)
{
    _pos.x += pos.x;
    _pos.y += pos.y;
}

void SpriteSDL2::move(float x, float y)
{
    _pos.x += x;
    _pos.y += y;
}

void SpriteSDL2::setOrigin(arcade::data::Vector2f origin)
{
    _pos.x += _origin.x / (_scale.x ? _scale.x : 1);
    _pos.y += _origin.y / (_scale.y ? _scale.y : 1);
    _origin = origin;
    _pos.x -= _origin.x * (_scale.x ? _scale.x : 1);
    _pos.y -= _origin.y * (_scale.y ? _scale.y : 1);
}

arcade::data::Vector2f SpriteSDL2::getOrigin()
{
    return _origin;
}

arcade::data::FloatRect SpriteSDL2::getLocalBounds()
{
    return arcade::data::FloatRect{0, 0, _originalSize.x, _originalSize.y};
}

arcade::data::FloatRect SpriteSDL2::getGlobalBounds()
{
    return arcade::data::FloatRect{_pos.y + _origin.y, _pos.x + _origin.x, _displayRect.x, _displayRect.y};
}

void SpriteSDL2::setScale(arcade::data::Vector2f scale)
{
    _displayRect.x /= _scale.x ? _scale.x : 1;
    _displayRect.y /= _scale.y ? _scale.y : 1;
    _scale = scale;
    _displayRect.x *= _scale.x;
    _displayRect.y *= _scale.y;
}

arcade::data::Vector2f SpriteSDL2::getScale()
{
    return _scale;
}

void SpriteSDL2::rotate(float angle)
{
    setRotation(getRotation() + angle);
}

void SpriteSDL2::setRotation(float angle)
{
    (void)angle;
}

float SpriteSDL2::getRotation()
{
    return 0;
}

void SpriteSDL2::setTextureRect(const arcade::data::IntRect &rect)
{
    _texture = rect;
}

arcade::data::IntRect SpriteSDL2::getTextureRect() const
{
    return _texture;
}

void SpriteSDL2::setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors)
{
    (void)asciiColors;
    SDL_SetTextureColorMod(_sprite.get(), color.r, color.g, color.b);
}