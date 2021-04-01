/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibNCRS
*/

#ifndef LIBNCRS_HPP_
#define LIBNCRS_HPP_

#include <fstream>

// #include <png.h>
#include <ncurses.h>
#include <chrono>
#include <tuple>
#include "Displayer.hpp"

class TextNCRS : public arcade::displayer::IText {
    public:
        TextNCRS(const std::string &text);
        TextNCRS();
        ~TextNCRS();

        void setText(const std::string &text) override;
        std::string getText() const override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void setFont(const std::string &fontPath) override;
        void setColor(arcade::data::Color color) override;
        arcade::data::Color getColor() const override;
        void setCharacterSize(unsigned int size) override;
        arcade::data::FloatRect getLocalBounds() override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;

        const char *getString() const;
        unsigned int getNcrsColor() const;

    protected:
    private:
        std::string _text;
        arcade::data::Vector2i _pos;
        arcade::data::Color _color;
        unsigned int _ncrsColor = COLOR_WHITE;
        arcade::data::Vector2i _origin;
};

class SpriteNCRS : public arcade::displayer::ISprite {
    public:
        SpriteNCRS();
        SpriteNCRS(const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1});
        ~SpriteNCRS();

        void setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite) override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void move(arcade::data::Vector2f pos) override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;
        arcade::data::FloatRect getLocalBounds() override;
        void setScale(arcade::data::Vector2f scale) override;
        arcade::data::Vector2f getScale() override;
        float getRotation() override;
        void setRotation(float angle) override;
        void rotate(float angle) override;
        void setTextureRect(const arcade::data::IntRect &rect) override;
        void setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors) override;

        std::vector<std::vector<chtype>> &getSprite();

    protected:
    private:
        std::vector<std::vector<chtype>> _sprite;
        std::vector<std::vector<chtype>> _originalSprite;
        arcade::data::Vector2i _pos;
        arcade::data::Vector2i _origin;
        arcade::data::Vector2f _scale = arcade::data::Vector2f{1, 1};
        float _rotation;
        arcade::data::IntRect _textureRect;
};

class LibNCRS : public arcade::displayer::IDisplay {
    public:
        LibNCRS();
        ~LibNCRS();

        int availableOptions() const override;
        void init() override;
        void stop() override;
        void clearWindow() override;
        void display() override;
        void restartClock() override;
        double getDeltaTime() override;
        arcade::data::Vector2u getWindowSize() override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        void draw(std::unique_ptr<arcade::displayer::ISprite> &sprite) override;
        std::unique_ptr<arcade::displayer::IText> createText() override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite() override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) override;

        std::ofstream &log() override;
        static NCURSES_PAIRS_T getNcrsColorPair(short fg, short bg);
        static std::pair<arcade::data::Color, NCURSES_PAIRS_T> colorToNcrsColor(arcade::data::Color color);

    protected:
    private:
        bool _eventFetched = false;
        std::vector<arcade::data::Event> _events;
        std::ofstream stream;
        std::chrono::time_point<std::chrono::high_resolution_clock> _timePoint;
};

#endif /* !LIBNCRS_HPP_ */
