/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibSDL2
*/

#ifndef LIBSDL2_HPP_
#define LIBSDL2_HPP_

#include <iostream>

// #include <SFML/Audio.hpp>
// #include <SFML/Graphics.hpp>
// #include <SFML/System.hpp>
// #include <SFML/Window.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <functional>
#include "Displayer.hpp"

typedef std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> SurfacePtr;
#define make_surface(__value)               (SurfacePtr{__value, SDL_FreeSurface})
typedef std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>> TexturePtr;
#define make_texture(__value)               (TexturePtr{__value, SDL_DestroyTexture})
typedef std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> RendererPtr;
#define make_renderer(__value)              (RendererPtr{__value, SDL_DestroyRenderer})
// typedef std::shared_ptr<SDL_Renderer> RendererShrdPtr;
// #define make_renderershrd(__value)          (RendererShrdPtr{__value, SDL_DestroyRenderer})

class TextSDL2 : public arcade::displayer::IText {
    public:
        TextSDL2();
        TextSDL2(const std::string &text);
        ~TextSDL2();

        void setText(const std::string &text) override;
        std::string getText() const override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void setFont(const std::string &fontPath) override;
        void setColor(arcade::data::Color color) override;
        arcade::data::Color getColor() const override;
        void setCharacterSize(unsigned int size) override;
        arcade::data::FloatRect getLocalBounds() override;
        arcade::data::FloatRect getGlobalBounds() override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;

        void draw();

    protected:
    private:
        typedef std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> FontPtr;
        #define make_font(__value)          (FontPtr{__value, TTF_CloseFont})

        std::string _string;
        unsigned int characterSize = 1;
        arcade::data::Color _color = arcade::data::Color::White;
        arcade::data::Vector2i _origin;
        SDL_Rect _rect;
        TexturePtr _text;
        FontPtr _font;
        std::string _fontPath;
};

class SpriteSDL2 : public arcade::displayer::ISprite {
    public:
        SpriteSDL2();
        SpriteSDL2(const std::string &spritePath, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1});
        ~SpriteSDL2();

        void setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite) override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void move(arcade::data::Vector2f pos) override;
        void move(float x, float y) override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;
        arcade::data::FloatRect getLocalBounds() override;
        arcade::data::FloatRect getGlobalBounds() override;
        void setScale(arcade::data::Vector2f scale) override;
        arcade::data::Vector2f getScale() override;
        void rotate(float angle) override;
        void setRotation(float angle) override;
        float getRotation() override;
        void setTextureRect(const arcade::data::IntRect &rect) override;
        arcade::data::IntRect getTextureRect() const override;
        void setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors) override;

        TexturePtr &getSprite();
        void draw();

    protected:
    private:
        TexturePtr _sprite;
        arcade::data::Vector2f _originalSize;
        arcade::data::Vector2f _scale;
        arcade::data::Vector2i _origin;
        arcade::data::FloatRect _texture;
        SDL_Rect _rect;
};

class LibSDL2 : public arcade::displayer::IDisplay {
    public:
        LibSDL2();
        ~LibSDL2();

        int availableOptions() const override;
        void init(const std::string &winName, unsigned int framesLimit = 60) override;
        void stop() override;
        bool isOpen() override;
        void clearWindow() override;
        void display() override;
        void restartClock() override;
        double getDeltaTime() override;
        double getFrameDuration() const;
        arcade::data::Vector2u getWindowSize() override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        void draw(std::unique_ptr<arcade::displayer::ISprite> &sprite) override;
        std::unique_ptr<arcade::displayer::IText> createText() override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite() override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) override;
        double scaleMoveX(double time) override;
        double scaleMoveY(double time) override;

        std::ofstream &log() { return stream; };

        static RendererPtr renderer;

    protected:
    private:
        typedef std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> WindowPtr;
        #define make_window(__value)        (WindowPtr{__value, SDL_DestroyWindow})

        WindowPtr _window;
        SDL_Event _event;
        bool _windowIsOpen = false;
        bool _eventsFetched = false;
        std::vector<arcade::data::Event> _events;
        std::ofstream stream;
        std::chrono::time_point<std::chrono::high_resolution_clock> _timePoint;
        double _lastFrameTime;
        unsigned int _frameLimit;
};

#endif /* !LIBSDL2_HPP_ */