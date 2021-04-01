/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Displayer
*/

#ifndef DISPLAYER_HPP_
#define DISPLAYER_HPP_

#include <fstream>

#include <vector>
#include <string>
#include <memory>
#include "Data.hpp"

namespace arcade
{
    namespace displayer
    {
        #define DISPLAYER_ENTRY_POINT       entry_point
        
        class IText {
            public:
                virtual void setText(const std::string &text) = 0;
                virtual std::string getText() const = 0;
                virtual void setPosition(arcade::data::Vector2f pos) = 0;
                virtual arcade::data::Vector2f getPosition() const = 0;
                virtual void setFont(const std::string &font) = 0;
                virtual void setColor(arcade::data::Color color) = 0;
                virtual arcade::data::Color getColor() const = 0;
                virtual void setCharacterSize(unsigned int size) = 0;
                virtual arcade::data::FloatRect getLocalBounds() = 0;
                virtual void setOrigin(arcade::data::Vector2f origin) = 0;
                virtual arcade::data::Vector2f getOrigin() = 0;
        };

        class ISprite {
            public:
                virtual void setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite) = 0;
                virtual void setPosition(arcade::data::Vector2f pos) = 0;
                virtual arcade::data::Vector2f getPosition() const = 0;
                virtual void move(arcade::data::Vector2f pos) = 0;
                virtual void setOrigin(arcade::data::Vector2f origin) = 0;
                virtual arcade::data::Vector2f getOrigin() = 0;
                virtual arcade::data::FloatRect getLocalBounds() = 0;
                virtual void setScale(arcade::data::Vector2f scale) = 0;
                virtual arcade::data::Vector2f getScale() = 0;
                virtual float getRotation() = 0;
                virtual void setRotation(float angle) = 0;
                virtual void rotate(float anle) = 0;
                virtual void setTextureRect(const arcade::data::IntRect &rect) = 0;
                virtual void setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors) = 0;
        };

        class IDisplay {
            public:
                enum AvailableOptions {
                    NO_OPTIONS          = 0,
                    SET_CHARACTER_SIZE  = 1 << 0,
                    MOUSE_MOVE          = 1 << 1,
                };
                #define isOptions(disp, opt)    ((disp)->availableOptions() & arcade::displayer::IDisplay::AvailableOptions::opt)

                virtual int availableOptions() const = 0;
                virtual void init() = 0;
                virtual void stop() = 0;
                virtual void clearWindow() = 0;
                virtual void display() = 0;
                virtual void restartClock() = 0;
                virtual double getDeltaTime() = 0;
                virtual arcade::data::Vector2u getWindowSize() = 0;
                virtual std::vector<arcade::data::Event> getEvents() = 0;
                virtual void draw(std::unique_ptr<IText> &text) = 0;
                virtual void draw(std::unique_ptr<ISprite> &sprite) = 0;
                virtual std::unique_ptr<IText> createText() = 0;
                virtual std::unique_ptr<IText> createText(const std::string &text) = 0;
                virtual std::unique_ptr<ISprite> createSprite() = 0;
                virtual std::unique_ptr<ISprite> createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) = 0;

                virtual std::ofstream &log() = 0;
        };
    } // namespace Displayer
} // namespace arcade

#endif /* !DISPLAYER_HPP_ */
