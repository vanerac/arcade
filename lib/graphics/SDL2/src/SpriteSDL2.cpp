/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SpriteSDL2
*/

#include "LibSDL2.hpp"

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
    auto surface = make_surface(SDL_LoadBMP(spritePath.c_str()));
    _sprite = make_texture(SDL_CreateTextureFromSurface(LibSDL2::renderer.get(), surface.get()));
    if (!_sprite) {
        if (!surface) {
            std::cout << "Double Fuck - ";
        }
        std::cout << "Fuck the sprite is null" << std::endl;
        return;
    }
    auto r = surface->clip_rect;
    _texture.width = r.w;
    _texture.height = r.h;
    _originalSize.x = r.w;
    _originalSize.y = r.h;
    _rect.w = r.w;
    _rect.h = r.h;
    _scale = {1, 1};
}

void SpriteSDL2::draw()
{
    auto t = getTextureRect();
    SDL_Rect texture;
    texture.x = t.left;
    texture.y = t.top;
    texture.w = t.width;
    texture.h = t.height;
    SDL_RenderCopy(LibSDL2::renderer.get(), _sprite.get(), &texture, &_rect);
}

void SpriteSDL2::setPosition(arcade::data::Vector2f pos)
{
    _rect.x = pos.x - _origin.x;
    _rect.y = pos.y - _origin.y;
}

arcade::data::Vector2f SpriteSDL2::getPosition() const
{
    return arcade::data::Vector2i{_rect.x + _origin.x, _rect.y + _origin.y};
}

void SpriteSDL2::move(arcade::data::Vector2f pos)
{
    _rect.x += pos.x;
    _rect.y += pos.y;
}

void SpriteSDL2::move(float x, float y)
{
    _rect.x += x;
    _rect.y += y;
}

void SpriteSDL2::setOrigin(arcade::data::Vector2f origin)
{
    _rect.x += _origin.x / (_scale.x ? _scale.x : 1);
    _rect.y += _origin.y / (_scale.y ? _scale.y : 1);
    _origin = origin;
    _rect.x -= _origin.x * (_scale.x ? _scale.x : 1);
    _rect.y -= _origin.y * (_scale.y ? _scale.y : 1);
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
    return arcade::data::IntRect{_rect.y + _origin.y, _rect.x + _origin.x, _rect.w, _rect.h};
}

void SpriteSDL2::setScale(arcade::data::Vector2f scale)
{
    _rect.w /= _scale.x ? _scale.x : 1;
    _rect.h /= _scale.y ? _scale.y : 1;
    _scale = scale;
    _rect.w *= _scale.x;
    _rect.h *= _scale.y;
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