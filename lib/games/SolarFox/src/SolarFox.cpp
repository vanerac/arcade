/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SolarFox
*/

#include <iostream>
#include <array>
#include <algorithm>
#include "SolarFox.hpp"
#include "Bullet.hpp"

solarfox::SolarFox::SolarFox()
{
}

solarfox::SolarFox::~SolarFox()
{
}

void solarfox::SolarFox::stop()
{
}

void solarfox::SolarFox::loadLevel()
{
    _isRestarting = true;
    init(_displayer);
}

void solarfox::SolarFox::restart()
{
    _isRestarting = true;
    _score = 0;
    _level = 1;
    init(_displayer);
}

unsigned int solarfox::SolarFox::getScore() const
{
    return _score;
}

arcade::data::FloatRect solarfox::SolarFox::findUnitCube(arcade::data::Vector2f pos) const
{
    arcade::data::FloatRect res;
    res.left = static_cast<int>((pos.x - _mapInitPos.x) / _unit.x) * _unit.x + _mapInitPos.x;
    res.top  = static_cast<int>((pos.y - _mapInitPos.y) / _unit.y) * _unit.y + _mapInitPos.y;
    res.width = _unit.x;
    res.height = _unit.y;
    return res;
}

float solarfox::SolarFox::findRotation(direction whereToPoint)
{
    static const std::array<std::pair<direction, float>, 4> directionToRotation = {
        std::pair<direction, float>{direction::Going_Down,  0},
        std::pair<direction, float>{direction::Going_Up,    180},
        std::pair<direction, float>{direction::Going_Left,  90},
        std::pair<direction, float>{direction::Going_Right, -90},
    };
    auto it = std::find_if(directionToRotation.begin(), directionToRotation.end(),
                        [whereToPoint](auto &pair) {
                            return pair.first == whereToPoint;
                        });
    if (it != directionToRotation.end()) {
        return (*it).second;
    }
    return 0;
}

void solarfox::SolarFox::createBullet(bool playerBuller, arcade::data::Vector2f initPos, direction direction, float lifedistance, float speed)
{
    std::string asciiTop    = direction <= direction::Going_Down ? "||" : "--";
    std::string asciiBottom = direction <= direction::Going_Down ? "||" : "--";
    std::unique_ptr<arcade::displayer::ISprite> sprite = _displayer->createSprite("ressources/solarfox/bullet.bmp", {asciiTop, asciiBottom});
    sprite->setScale({2, (_unit.y / 2) / sprite->getLocalBounds().height});
    sprite->setOrigin({sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2});
    sprite->setPosition(initPos);
    sprite->setRotation(findRotation(direction));
    arcade::data::Vector2f directionUnit;
    directionUnit.x = (direction >  direction::Going_Down ? -1 + (2 * (direction - 2)) : 0);
    directionUnit.y = (direction <= direction::Going_Down ? -1 + (2 * direction) : 0);
    if (playerBuller) {
        _pbullets.emplace_back(std::make_unique<solarfox::Bullet>(std::move(sprite), directionUnit, lifedistance, speed));
    } else {
        _ebullets.emplace_back(std::make_unique<solarfox::Bullet>(std::move(sprite), directionUnit, lifedistance, speed));
    }
}

void solarfox::SolarFox::restartClock()
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

double solarfox::SolarFox::getTimePassed() const
{
    return std::chrono::duration_cast
        <
        std::chrono::duration<double, std::ratio<1>>
        >
            (std::chrono::high_resolution_clock::now() - _timePoint).count();
}