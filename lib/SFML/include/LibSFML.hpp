/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibSFML
*/

#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include "Displayer.hpp"

class TextSFML : public arcade::displayer::IText {
    public:
        TextSFML();
        TextSFML(const std::string &text);
        ~TextSFML();

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
        
        sf::Text &getText();

    protected:
    private:
        sf::Text _text;
        sf::Font _font;
};

class SpriteSFML : public arcade::displayer::ISprite {
    public:
        SpriteSFML();
        SpriteSFML(const std::string &spritePath, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1});
        ~SpriteSFML();

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

        sf::Sprite &getSprite();

    protected:
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
};

class LibSFML : public arcade::displayer::IDisplay {
    public:
        LibSFML();
        ~LibSFML();

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

        std::ofstream &log() { return stream; };

    protected:
    private:
        bool _eventsFetched = false;
        std::vector<arcade::data::Event> _events;
        std::ofstream stream;
        sf::RenderWindow _window;
        sf::Font _font;
        sf::Clock _clock;
        std::chrono::time_point<std::chrono::high_resolution_clock> _timePoint;
};

#endif /* !LIBSFML_HPP_ */
