/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Enemy
*/

#include <cmath>
#include "Enemy.hpp"

solarfox::Enemy::Enemy(std::unique_ptr<arcade::displayer::ISprite> sprite, arcade::data::Vector2f start, arcade::data::Vector2f end) : _sprite(std::move(sprite)), _start(start), _end(end)
{
    if (start.x == end.x) {
        _unitMove.y = start.y < end.y ? 1 : -1;
        _rotation   = start.y < end.y ? solarfox::direction::Going_Left : solarfox::direction::Going_Right;
    } else if (start.y == end.y) {
        _unitMove.x = start.x < end.x ? 1 : -1;
        _rotation   = start.x < end.x ? solarfox::direction::Going_Down : solarfox::direction::Going_Up;
    }
    float diff = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
    _distBeforeShot = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
    _shot = false;
    restartClock();
}

solarfox::Enemy::~Enemy()
{
}

arcade::data::Vector2f solarfox::Enemy::getUnitMove() const
{
    return {_unitMove.x * _direction, _unitMove.y * _direction};
}

solarfox::direction solarfox::Enemy::getDirection() const
{
    return _rotation;
}

std::unique_ptr<arcade::displayer::ISprite> &solarfox::Enemy::getSprite()
{
    return _sprite;
}

void solarfox::Enemy::resetPos()
{
    // float diff = std::sqrt(std::pow(_end.x - _start.x, 2) + std::pow(_end.y - _start.y, 2));    
    // float off = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
    // if (_rotation == direction::Going_Up) {
    //     _sprite->setPosition(_start + arcade::data::Vector2f{-off, 0});
    // } else if (_rotation == direction::Going_Right) {
    //     _sprite->setPosition(_start + arcade::data::Vector2f{0, -off});
    // } else if (_rotation == direction::Going_Down) {
    //     _sprite->setPosition(_start + arcade::data::Vector2f{off, 0});
    // } else if (_rotation == direction::Going_Left) {
    //     _sprite->setPosition(_start + arcade::data::Vector2f{0, off});
    // }
    _sprite->setPosition(_start);
}

void solarfox::Enemy::shot()
{
    restartClock();
    _wasShot = true;
}

bool solarfox::Enemy::shouldMove()
{
    if (_wasShot && getTimePassed() < 1) {
        return false;
    } else if (_wasShot) {
        _wasShot = false;
    }
    return true;
}

bool solarfox::Enemy::shouldShot()
{
    if (_wasShot && getTimePassed() < 1) {
        return false;
    } else if (_wasShot) {
        _wasShot = false;
    }
    if (_shot) {
        return false;
    }
    auto pos = _sprite->getPosition();
    auto dest = _direction > 0 ? _end : _start;
    float diff = std::sqrt(std::pow(dest.x - pos.x, 2) + std::pow(dest.y - pos.y, 2));
    if (diff <= _distBeforeShot) {
        diff = std::sqrt(std::pow(_end.x - _start.x, 2) + std::pow(_end.y - _start.y, 2));
        _distBeforeShot = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
        _shot = true;
        return true;
    }
    return false;
}

void solarfox::Enemy::update()
{
    auto pos = _sprite->getPosition();

    if (
        (_unitMove.x < 0 && ((pos.x < _end.x && _direction > 0) || (pos.x > _start.x && _direction < 0)))
    ||  (_unitMove.x > 0 && ((pos.x > _end.x && _direction > 0) || (pos.x < _start.x && _direction < 0)))
    ||  (_unitMove.y < 0 && ((pos.y < _end.y && _direction > 0) || (pos.y > _start.y && _direction < 0)))
    ||  (_unitMove.y > 0 && ((pos.y > _end.y && _direction > 0) || (pos.y < _start.y && _direction < 0)))
    ) {
        _direction = -_direction;
        _shot = false;
    }
}

void solarfox::Enemy::restartClock()
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

double solarfox::Enemy::getTimePassed() const
{
    return std::chrono::duration_cast
        <
        std::chrono::duration<double, std::ratio<1>>
        >
            (std::chrono::high_resolution_clock::now() - _timePoint).count();
}