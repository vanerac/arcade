/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <cstdint>

namespace arcade
{
    namespace data
    {
        enum EventType
        {
            WINDOW_CLOSED,
            KEY_PRESSED,
            MOUSE_MOVED,
            MOUSE_PRESSED,
            MOUSE_RELEASED,
        };
        enum        KeyCode
        {
            ENTER               = 10,
            ESCAPE              = 27,
            SPACE               = 32,
            SPECIAL_KEYS_START  = 257,
            DOWN                = 258,
            UP                  = 259,
            LEFT                = 260,
            RIGHT               = 261,
            BACKSPACE           = 263,
        };
        enum MouseBtn
        {
            BTN_1,
            BTN_2,
            BTN_3,
            BTN_4,
        };

        struct Event
        {
            Event() : type(static_cast<EventType>(0)), x(0), y(0) {};
            Event(EventType type) : type(type), x(0), y(0) {};
            Event(EventType type, MouseBtn btn, int x, int y) : type(type), btn(btn), x(x), y(y) {};
            Event(EventType type, int x, int y) : type(type), x(x), y(y) {};
            Event(EventType type, KeyCode keyCode) : type(type), keyCode(keyCode), x(0), y(0) {};
            Event(EventType type, char key) : type(type), key(key), x(0), y(0) {};

            EventType type;
            union
            {
                KeyCode keyCode = static_cast<KeyCode>(0);
                char key;
                MouseBtn btn;
            };
            struct
            {
                int x;
                int y;
            };
        };

        template<typename T>
        struct Vector2
        {
            Vector2() : x(0), y(0) {};
            Vector2(T x) : x(x), y(0) {};
            Vector2(T x, T y) : x(x), y(y) {};
            template<typename U>
            Vector2(const Vector2<U> &vect) : x(static_cast<T>(vect.x)), y(static_cast<T>(vect.y)) {};

            template<typename U>
            Vector2<T> &operator=(const Vector2<U> &other) { x = static_cast<T>(other.x); y = static_cast<T>(other.y); return *this; };

            template<typename U>
            Vector2<T> &operator+=(const Vector2<U> &other) { x += static_cast<T>(other.x); y += static_cast<T>(other.y); return *this; };

            Vector2<T> operator+(const Vector2<T> &other) const { return arcade::data::Vector2<T>{x + other.x, y + other.y}; };

            template<typename U>
            bool operator==(const Vector2<U> &other) const { return x == static_cast<T>(other.x) && y == static_cast<T>(other.y); };

            Vector2<T> &move(T x) { this->x += x; return *this; };
            Vector2<T> &move(T x, T y) { this->x += x; this->y += y; return *this; };
            template<typename U>
            Vector2<T> &move(const Vector2<U> &other) { x += static_cast<T>(other.x); y += static_cast<T>(other.y); return *this; };

            T x;
            T y;
        };

        typedef Vector2<int>          Vector2i;
        typedef Vector2<unsigned int> Vector2u;
        typedef Vector2<float>        Vector2f;

        template<typename T>
        struct Rect
        {
            Rect() : top(0), left(0), width(0), height(0) {};
            Rect(T width, T height) : top(0), left(0), width(width), height(height) {};
            Rect(T top, T left, T width, T height) : top(top), left(left), width(width), height(height) {};
            template<typename U>
            explicit Rect(U top, U left, U width, U height) : top(static_cast<T>(top)), left(static_cast<T>(left)),
                                                                width(static_cast<T>(width)), height(static_cast<T>(height)) {};
            template<typename U>
            Rect(const Rect<U> &rect) : top(static_cast<T>(rect.top)), left(static_cast<T>(rect.left)),
                                        width(static_cast<T>(rect.width)), height(static_cast<T>(rect.height)) {};

            T top;
            T left;
            T width;
            T height;
        };
        
        typedef Rect<int>       IntRect;
        typedef Rect<float>     FloatRect;

        struct Color
        {
            Color() : r(255), g(255), b(255), a(255) {};
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
                : r(red), g(green), b(blue), a(alpha) {};

            bool operator==(const Color &other) const { return r == other.r && g == other.g && b == other.b && a == other.a; };

            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;

            static const Color Black;
            static const Color White;
            static const Color Red;
            static const Color Green;
            static const Color Blue;
            static const Color Yellow;
            static const Color Magenta;
            static const Color Cyan;
            static const Color Transparent;
        };
    } // namespace data
} // namespace arcade

#include <iostream>

template<typename T>
std::ostream &operator<<(std::ostream &s, const arcade::data::Vector2<T> &vect) {
    s << '[' << vect.x << ", " << vect.y << ']';
    return s;
}

template<typename T>
std::ostream &operator<<(std::ostream &s, const arcade::data::Rect<T> &rect) {
    s << "pos:[" << rect.left << ", " << rect.top << "]-size[" << rect.width << ", " << rect.height << "]";
    return s;
}

#endif /* !DATA_HPP_ */
