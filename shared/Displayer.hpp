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
                virtual arcade::data::FloatRect getLocalBounds() const = 0;
                virtual arcade::data::FloatRect getGlobalBounds() const = 0;
                virtual void setOrigin(arcade::data::Vector2f origin) = 0;
                virtual arcade::data::Vector2f getOrigin() const = 0;
        };

        class ISprite {
            public:
                virtual void setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite) = 0;
                virtual void setPosition(arcade::data::Vector2f pos) = 0;
                virtual arcade::data::Vector2f getPosition() const = 0;
                virtual void move(arcade::data::Vector2f pos) = 0;
                virtual void move(float x, float y) = 0;
                virtual void setOrigin(arcade::data::Vector2f origin) = 0;
                virtual arcade::data::Vector2f getOrigin() const = 0;
                virtual arcade::data::FloatRect getLocalBounds() const = 0;
                virtual arcade::data::FloatRect getGlobalBounds() const = 0;
                virtual void setScale(arcade::data::Vector2f scale) = 0;
                virtual arcade::data::Vector2f getScale() const = 0;
                virtual void rotate(float anle) = 0;
                virtual void setRotation(float angle) = 0;
                virtual float getRotation() const = 0;
                virtual void setTextureRect(const arcade::data::IntRect &rect) = 0;
                virtual arcade::data::IntRect getTextureRect() const = 0;
                virtual void setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors) = 0;
        };

        class IDisplay {
            public:
                enum AvailableOptions {
                    NO_OPTIONS          = 0,
                    SET_CHARACTER_SIZE  = 1 << 0,
                    MOUSE_MOVE          = 1 << 1,
                    SETTING_FONTS       = 1 << 2,
                };
                #define isOptions(disp, opt)    ((disp)->availableOptions() & arcade::displayer::IDisplay::AvailableOptions::opt)

                virtual int availableOptions() const = 0;
                virtual void init(const std::string &winName, unsigned int framesLimit = 60) = 0;
                virtual void stop() = 0;
                virtual bool isOpen() const = 0;
                virtual void clearWindow() = 0;
                virtual void display() = 0;
                virtual void restartClock() = 0;
                virtual double getDeltaTime() const = 0;
                virtual arcade::data::Vector2u getWindowSize() const = 0;
                virtual std::vector<arcade::data::Event> getEvents() = 0;
                virtual void draw(std::unique_ptr<IText> &text) = 0;
                virtual void draw(std::unique_ptr<ISprite> &sprite) = 0;
                virtual std::unique_ptr<IText> createText() const = 0;
                virtual std::unique_ptr<IText> createText(const std::string &text) const = 0;
                virtual std::unique_ptr<ISprite> createSprite() const = 0;
                virtual std::unique_ptr<ISprite> createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) const = 0;
                virtual double scaleMoveX(double time) const = 0;
                virtual double scaleMoveY(double time) const = 0;

                virtual std::ofstream &log() = 0;
        };
    } // namespace Displayer

    template<typename T, typename U>
    constexpr bool isOverlap(const arcade::data::Rect<T> &a, U x, U y) {
        if (a.left <= x && x <= (a.left + a.width)
        && a.top <= y && y <= (a.top + a.height)) {
            return true;
        }
        return false;
    };
    template<typename T, typename U>
    constexpr bool isOverlap(const arcade::data::Rect<T> &a, const arcade::data::Vector2<U> &b) {
        if (a.left <= b.x && b.x <= (a.left + a.width)
        && a.top <= b.y && b.y <= (a.top + a.height)) {
            return true;
        }
        return false;
    };
    template<typename T>
    constexpr bool isOverlap(const arcade::data::Rect<T> &a, const arcade::data::Rect<T> &b) {
        if ((
        (  (a.left <= b.left && b.left <= (a.left + a.width))
        || (a.left <= (b.left + b.width) && (b.left + b.width) <= (a.left + a.width))
        )
        &&
        (  (a.top <= b.top && b.top <= (a.top + a.height))
        || (a.top <= (b.top + b.height) && (b.top + b.height) <= (a.top + a.height))
        )
        )
        ||
        (
        (  (b.left <= a.left && a.left <= (b.left + b.width))
        || (b.left <= (a.left + a.width) && (a.left + a.width) <= (b.left + b.width))
        )
        &&
        (  (b.top <= a.top && a.top <= (b.top + b.height))
        || (b.top <= (a.top + a.height) && (a.top + a.height) <= (b.top + b.height))
        )
        )) {
            return true;
        }
        return false;
    };
} // namespace arcade

#endif /* !DISPLAYER_HPP_ */
