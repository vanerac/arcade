/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Bullet
*/

#include "Bullet.hpp"

solarfox::Bullet::Bullet(std::unique_ptr<arcade::displayer::ISprite> sprite, arcade::data::Vector2f unitMove, float lifedistance, float speed) : _sprite(std::move(sprite)), _unitMove(unitMove), _lifedistance(lifedistance), _speed(speed)
{
    _endPos = _sprite->getPosition();
    if (_unitMove.y != 0) {
        _endPos.y += lifedistance * _unitMove.y;
    }
    if (_unitMove.x != 0) {
        _endPos.x += lifedistance * _unitMove.x;
    }
}

solarfox::Bullet::~Bullet()
{
}

bool solarfox::Bullet::shouldDie() const
{
    auto pos = _sprite->getPosition();

    if (_unitMove.x != 0 && _unitMove.y == 0) {
        return (_unitMove.x < 0 ? pos.x <= _endPos.x : _endPos.x <= pos.x);
    } else if (_unitMove.y != 0 && _unitMove.x == 0) {
        return (_unitMove.y < 0 ? pos.y <= _endPos.y : _endPos.y <= pos.y);
    } else {
        return (_unitMove.x < 0 ? pos.x <= _endPos.x : _endPos.x <= pos.x)
                && (_unitMove.y < 0 ? pos.y <= _endPos.y : _endPos.y <= pos.y);
    }
}

arcade::data::Vector2f solarfox::Bullet::getUnitMove() const
{
    return _unitMove;
}

std::unique_ptr<arcade::displayer::ISprite> &solarfox::Bullet::getSprite()
{
    return _sprite;
}

float solarfox::Bullet::getSpeed()
{
    return _speed;
}

bool solarfox::Bullet::doesCollide(arcade::data::FloatRect rect)
{
    return false;
}

bool solarfox::Bullet::doesCollide(std::vector<std::unique_ptr<arcade::displayer::ISprite>> &objects)
{
    return false;
}