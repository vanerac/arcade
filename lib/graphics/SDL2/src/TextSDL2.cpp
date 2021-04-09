/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** TextSDL2
*/

#include "LibSDL2.hpp"
#include "Errors.hpp"

TextSDL2::TextSDL2()
{
}

TextSDL2::TextSDL2(const std::string &text)
{
    setText(text);
}

TextSDL2::~TextSDL2()
{
}

void TextSDL2::draw()
{
    if (_text && SDL_RenderCopy(LibSDL2::renderer.get(), _text.get(), nullptr, &_rect) < 0) {
        throw arcade::errors::Error(std::string{"Unexpected error while drawing a text: "} + SDL_GetError());
    }
}

void TextSDL2::setText(const std::string &text)
{
    _string = text;
    if (_font) {
        SDL_Color color = {.r = _color.r, .g = _color.g, .b = _color.b, .a = _color.a};
        SurfacePtr surface = make_surface(TTF_RenderText_Solid(_font.get(), text.c_str(), color));
        if (!surface
        || !(_text = make_texture(SDL_CreateTextureFromSurface(LibSDL2::renderer.get(), surface.get())))
        || SDL_QueryTexture(_text.get(), NULL, NULL, &_rect.w, &_rect.h) < 0) {
            throw arcade::errors::Error("The text could not been set properly ('" + text.substr(0, 10) + (text.size() > 10 ? "[...]" : "") + "'): " + SDL_GetError());
        }
    }
}

std::string TextSDL2::getText() const
{
    return _string;
}

void TextSDL2::setPosition(arcade::data::Vector2f pos)
{
    _rect.x = pos.x - _origin.x;
    _rect.y = pos.y - _origin.y;
}

arcade::data::Vector2f TextSDL2::getPosition() const
{
    return arcade::data::Vector2i{_rect.x + _origin.x, _rect.y + _origin.y};
}

void TextSDL2::setFont(const std::string &fontPath)
{
    _fontPath = fontPath;
    if (!(_font = make_font(TTF_OpenFont(fontPath.c_str(), characterSize)))) {
        throw arcade::errors::Error("Failed to load font '" + fontPath + "': " + SDL_GetError());
    }
    setText(_string);
}

void TextSDL2::setColor(arcade::data::Color color)
{
    _color = color;
    setText(_string);
}

arcade::data::Color TextSDL2::getColor() const
{
    return _color;
}

void TextSDL2::setCharacterSize(unsigned int size)
{
    characterSize = size;
    if (_fontPath.size()) {
        setFont(_fontPath);
    }
}

arcade::data::FloatRect TextSDL2::getLocalBounds()
{
    return arcade::data::FloatRect{0, 0, _rect.w, _rect.h};
}

arcade::data::FloatRect TextSDL2::getGlobalBounds()
{
    return arcade::data::FloatRect{_rect.y, _rect.x, _rect.w, _rect.h};
}

void TextSDL2::setOrigin(arcade::data::Vector2f origin)
{
    _rect.x += _origin.x;
    _rect.y += _origin.y;
    _origin = origin;
    _rect.x -= _origin.x;
    _rect.y -= _origin.y;
}

arcade::data::Vector2f TextSDL2::getOrigin()
{
    return _origin;
}