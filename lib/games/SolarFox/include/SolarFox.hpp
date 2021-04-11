/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_

#include <iostream>

#include <chrono>
#include "Games.hpp"
#include "solarfoxData.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

namespace solarfox
{
    class SolarFox : public arcade::games::IGame {
        public:
            SolarFox();
            ~SolarFox();

            void init(std::shared_ptr<arcade::displayer::IDisplay> &disp) override;
            void stop() override;
            arcade::games::GameStatus update() override;
            unsigned int getScore() override;
            void restart() override;

            void handleEvents();
            void updateEnemies();
            bool updateBullets();
            bool updatePlayer();
            void draw();

        protected:
        private:
            arcade::data::FloatRect findUnitCube(arcade::data::Vector2f pos) const;
            float findRotation(direction whereToPoint);
            void createMap();
            void createBullet(bool playerBuller, arcade::data::Vector2f initPos, direction direction, float lifedistance, float speed = 0.5f);
            void createEnemy(direction wallSide);
            void loadLevel();
            void restartClock();
            double getTimePassed() const;

            std::shared_ptr<arcade::displayer::IDisplay> _displayer;
            arcade::data::Vector2f _unit;
            arcade::data::Vector2u _mapSize;
            arcade::data::Vector2f _mapInitPos;
            std::unique_ptr<arcade::displayer::ISprite> _player;
            direction _playerDirection = direction::Going_Down;
            direction _wichedDirection = direction::No_Direction;
            std::vector<std::unique_ptr<arcade::displayer::ISprite>> _walls;
            std::vector<std::unique_ptr<solarfox::Bullet>> _ebullets;
            std::vector<std::unique_ptr<solarfox::Bullet>> _pbullets;
            std::vector<std::unique_ptr<solarfox::Enemy>>  _enemies;
            std::vector<std::unique_ptr<arcade::displayer::ISprite>> _collectables;
            std::unique_ptr<arcade::displayer::IText> _lvlText;
            std::unique_ptr<arcade::displayer::IText> _scoreText;
            std::unique_ptr<arcade::displayer::IText> _delayText;
            std::vector<std::vector<int>> _map;
            int _level = 1;
            unsigned int _score = 0;
            bool _isRestarting = false;
            std::chrono::time_point<std::chrono::high_resolution_clock> _timePoint;
    };
} // namespace soloarfox


std::ostream &operator<<(std::ostream &s, const solarfox::direction &d);

#endif /* !SOLARFOX_HPP_ */