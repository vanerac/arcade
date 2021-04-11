/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SolarFoxInit
*/

#include <algorithm>
#include <cmath>
#include "SolarFox.hpp"

std::ostream &operator<<(std::ostream &s, const solarfox::direction &d) {
    if (d == solarfox::direction::Going_Up) {
        s << "Going_Up";
    } else if (d == solarfox::direction::Going_Down) {
        s << "Going_Down";
    } else if (d == solarfox::direction::Going_Left) {
        s << "Going_Left";
    } else if (d == solarfox::direction::Going_Right) {
        s << "Going_Right";
    } else {
        s << "No_Direction";
    }
    return s;
};

void solarfox::SolarFox::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    _displayer = disp;
    createMap();

    arcade::data::Vector2f winSize = _displayer->getWindowSize();
    _mapSize = {static_cast<unsigned int>(_map[0].size()) + 2, static_cast<unsigned int>(_map.size()) + 2};
    _unit.y = isOptions(_displayer, SET_CHARACTER_SIZE) ? winSize.y * 0.85f / _mapSize.y : 2;
    _unit.x = _unit.y;
    _mapInitPos.x = winSize.x / 2 - ((_mapSize.x / 2) * _unit.x + ((_mapSize.x % 2) * (_unit.x / 2)));
    _mapInitPos.y = winSize.y / 2 - ((_mapSize.y / 2) * _unit.y + ((_mapSize.y % 2) * (_unit.y / 2)));
    int characterSize = isOptions(_displayer, SET_CHARACTER_SIZE) ? 40 : 1;
    const int yOffset = winSize.y * 0.02f;


    if (!_isRestarting) {
        _pbullets.clear();
        _ebullets.clear();
    }



    // --- Level and Score text ---
    _lvlText = _displayer->createText("Lv: " + std::to_string(_level));
    _lvlText->setCharacterSize(characterSize);
    _lvlText->setFont("ressources/font.ttf");
    _lvlText->setPosition({winSize.x * 0.02f, winSize.y * 0.02f});
    _scoreText = _displayer->createText("Score: " + std::to_string(_score));
    _scoreText->setCharacterSize(characterSize);
    _scoreText->setFont("ressources/font.ttf");
    _scoreText->setPosition({_lvlText->getGlobalBounds().left, _lvlText->getGlobalBounds().top + characterSize + yOffset});



    // --- Enemies ---
    if (!_isRestarting) {
        _enemies.clear();
        createEnemy(direction::Going_Up);
        createEnemy(direction::Going_Right);
        createEnemy(direction::Going_Down);
        createEnemy(direction::Going_Left);
    } else {
        std::for_each(_enemies.begin(), _enemies.end(), [](auto &e) { e->resetPos(); });
    }



    // --- Walls ---
    if (!_isRestarting)
    {
        arcade::data::Vector2f initPos = _mapInitPos;
        arcade::data::Vector2f pos{initPos};
        _walls.clear();
        for (unsigned int y = 0; y < _mapSize.y; ++y, pos = initPos.move(0, _unit.y)) {
            unsigned int nbTodo = (y == 0 || y == (_mapSize.y - 1)) ? _mapSize.x : 2;
            float xMove = (y == 0 || y == (_mapSize.y - 1)) ? _unit.x : ((_mapSize.x - 1) * _unit.x);
            for (unsigned int x = 0; x < nbTodo; ++x, pos.move(xMove)) {
                _walls.push_back(_displayer->createSprite("ressources/solarfox/block.bmp", {"##", "##"}));
                auto &w = _walls[_walls.size() - 1];
                w->setScale({_unit.x / w->getLocalBounds().width, _unit.y / w->getLocalBounds().height});
                w->setPosition(pos);
            }
        }
    }



    // --- Collectables and Player ---
    {
        arcade::data::Vector2f initPos = _mapInitPos;
        initPos.move(_unit.x, _unit.y);
        arcade::data::Vector2f pos{initPos};
        _collectables.clear();
        for (unsigned int y = 1; y < _mapSize.y - 2; ++y, pos = initPos.move(0, _unit.y)) {
            for (unsigned int x = 1; x < _mapSize.x - 2; ++x, pos.move(_unit.x)) {
                if (_map[y - 1][x - 1] == 1) {
                    _collectables.push_back(_displayer->createSprite("ressources/solarfox/asteroid.bmp", {"XX", "XX"}));
                    auto &c = _collectables[_collectables.size() - 1];
                    c->setScale({_unit.x / c->getLocalBounds().width, _unit.y / c->getLocalBounds().height});
                    c->setPosition(pos);
                } else if (_map[y - 1][x - 1] == 2) {
                    _player = _displayer->createSprite("ressources/solarfox/player.bmp", {"##", "||"});
                    _player->setScale({_unit.x / _player->getLocalBounds().width, _unit.y / _player->getLocalBounds().height});
                    _player->setOrigin({_player->getLocalBounds().width / 2, _player->getLocalBounds().height / 2});
                    arcade::data::Vector2f p{_player->getGlobalBounds().width / 2, _player->getGlobalBounds().height / 2};
                    _player->setPosition(pos + p);
                    _player->setRotation(findRotation(direction::Going_Right));
                    _playerDirection = Going_Right;
                }
            }
        }
    }



    // --- Delay Text ---
    _delayText = _displayer->createText("-- 3 --");
    _delayText->setColor(arcade::data::Color::Red);
    _delayText->setCharacterSize(characterSize);
    _delayText->setFont("ressources/font.ttf");
    _delayText->setOrigin({_delayText->getLocalBounds().width / 2, 0});
    _delayText->setPosition({winSize.x * 0.50f, static_cast<float>(yOffset)});
    _isRestarting = false;
    restartClock();
}

void solarfox::SolarFox::createEnemy(direction wallSide)
{
    std::string asciiTop   = wallSide <= direction::Going_Down ? "##" : "##";
    std::string asciiBotom = wallSide <= direction::Going_Down ? "MM" : "EE";
    auto sprite = _displayer->createSprite("ressources/solarfox/enemy.bmp", {asciiTop, asciiBotom});
    sprite->setScale({_unit.x / sprite->getLocalBounds().width, _unit.y / sprite->getLocalBounds().height});
    arcade::data::Vector2f start;
    arcade::data::Vector2f end;
    if (wallSide == direction::Going_Up) {
        start = {_mapInitPos.x + (_unit.x * 1.5f), _mapInitPos.y + (_unit.y * 1.5f)};
        end   = {_mapInitPos.x + (_unit.x * (_mapSize.x - 2 + 0.5f)), _mapInitPos.y + (_unit.y * 1.5f)};
        float diff = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));    
        float off = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
        sprite->setPosition(start + arcade::data::Vector2f{off, 0});
    } else if (wallSide == direction::Going_Right) {
        start = {_mapInitPos.x + (_unit.x * (_mapSize.x - 2)) + (_unit.x / 2), _mapInitPos.y + (_unit.y * 1.5f)};
        end   = {_mapInitPos.x + (_unit.x * (_mapSize.x - 2)) + (_unit.x / 2), _mapInitPos.y + (_unit.y * (_mapSize.y - 2) + 0.5f)};
        float diff = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));    
        float off = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
        sprite->setPosition(start + arcade::data::Vector2f{0, off});
    } else if (wallSide == direction::Going_Down) {
        start = {_mapInitPos.x + (_unit.x * (_mapSize.x - 2 + 0.5f)), _mapInitPos.y + (_unit.y * (_mapSize.y - 2)) + (_unit.y / 2)};
        end   = {_mapInitPos.x + (_unit.x * 1.5f), _mapInitPos.y + (_unit.y * (_mapSize.y - 2)) + (_unit.y / 2)};
        float diff = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));    
        float off = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
        sprite->setPosition(start + arcade::data::Vector2f{-off, 0});
    } else if (wallSide == direction::Going_Left) {
        start = {_mapInitPos.x + (_unit.x * 1.5f), _mapInitPos.y + (_unit.y * (_mapSize.y - 2 + 0.5f))};
        end   = {_mapInitPos.x + (_unit.x * 1.5f), _mapInitPos.y + (_unit.y * 1.5f)};
        float diff = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));    
        float off = (diff * 0.15f) + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / ((diff * (1 - 0.15f)) - (diff * 0.15f))));
        sprite->setPosition(start + arcade::data::Vector2f{0, -off});
    }
    wallSide = static_cast<direction>(wallSide <= direction::Going_Down ? ((wallSide + 1) % 2) : (((wallSide - 1) % 2) + 2));
    sprite->setOrigin({sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2});
    sprite->setRotation(findRotation(wallSide));
    _enemies.emplace_back(std::make_unique<solarfox::Enemy>(std::move(sprite), start, end));
}

void solarfox::SolarFox::createMap()
{
    if (_level == 1) {
        _map = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 2, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };
    } else if (_level == 2) {
        _map = {
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        };
    } else if (_level == 3) {
        _map = {
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 2, 0, 0, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        };
    } else if (_level == 4) {
        _map = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 2, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };
    }
}