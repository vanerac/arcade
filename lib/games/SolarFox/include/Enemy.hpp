/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Enemy
*/

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <chrono>
#include "solarfoxData.hpp"
#include "Displayer.hpp"

namespace solarfox
{
    class Enemy {
        public:
            Enemy(std::unique_ptr<arcade::displayer::ISprite> sprite, arcade::data::Vector2f start, arcade::data::Vector2f end);
            ~Enemy();

            arcade::data::Vector2f getUnitMove() const;
            solarfox::direction getDirection() const;
            std::unique_ptr<arcade::displayer::ISprite> &getSprite();
            void shot();
            void update();
            bool shouldShot();
            bool shouldMove();
            void resetPos();

        protected:
        private:
            void restartClock();
            double getTimePassed() const;

            std::unique_ptr<arcade::displayer::ISprite> _sprite;
            arcade::data::Vector2f _start;
            arcade::data::Vector2f _end;
            arcade::data::Vector2f _unitMove;
            solarfox::direction _rotation;
            int _direction = 1;
            float _distBeforeShot;
            bool _shot;
            bool _wasShot;
            std::chrono::time_point<std::chrono::high_resolution_clock> _timePoint;
    };   
} // namespace solarfox

#endif /* !ENEMY_HPP_ */
