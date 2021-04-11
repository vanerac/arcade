/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "Data.hpp"
#include "Displayer.hpp"
#include "solarfoxData.hpp"

namespace solarfox
{
    class Bullet {
        public:
            Bullet(std::unique_ptr<arcade::displayer::ISprite> sprite, arcade::data::Vector2f unitMove, float lifedistance, float speed = 0.5f);
            ~Bullet();

            bool shouldDie() const;
            arcade::data::Vector2f getUnitMove() const;
            std::unique_ptr<arcade::displayer::ISprite> &getSprite();
            float getSpeed();

            bool doesCollide(arcade::data::FloatRect rect);
            bool doesCollide(std::vector<std::unique_ptr<arcade::displayer::ISprite>> &objects);

        protected:
        private:
            std::unique_ptr<arcade::displayer::ISprite> _sprite;
            arcade::data::Vector2f _endPos;
            arcade::data::Vector2f _unitMove;
            float _lifedistance;
            float _speed;
    };
} // namespace solarfox

#endif /* !BULLET_HPP_ */
