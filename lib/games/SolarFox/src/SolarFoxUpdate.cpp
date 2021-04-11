/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** SolarFoxUpdate
*/

#include <array>
#include <algorithm>
#include "SolarFox.hpp"

arcade::games::GameStatus solarfox::SolarFox::update()
{
    if (getTimePassed() <= 3) {
        draw();
        return arcade::games::GameStatus::PLAYING;
    }
    handleEvents();
    updateEnemies();
    if (updateBullets() || updatePlayer()) {
        return arcade::games::GameStatus::GAME_ENDED;
    }
    draw();
    return arcade::games::GameStatus::PLAYING;
}

void solarfox::SolarFox::handleEvents()
{
    static const std::array<std::pair<arcade::data::KeyCode, direction>, 4> keyToDirection = {
        std::pair<arcade::data::KeyCode, direction>{arcade::data::KeyCode::UP,    direction::Going_Up},
        std::pair<arcade::data::KeyCode, direction>{arcade::data::KeyCode::DOWN,  direction::Going_Down},
        std::pair<arcade::data::KeyCode, direction>{arcade::data::KeyCode::LEFT,  direction::Going_Left},
        std::pair<arcade::data::KeyCode, direction>{arcade::data::KeyCode::RIGHT, direction::Going_Right},
    };
    auto events = _displayer->getEvents();

    for (auto &event : events) {
        const auto findKey = [&event](const std::pair<arcade::data::KeyCode, direction> &pair) {
                                                return pair.first == event.keyCode;
                                            };
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            if (event.keyCode == arcade::data::KeyCode::SPACE) {
                createBullet(true, _player->getPosition(), _playerDirection,
                    3 * (_playerDirection <= solarfox::direction::Going_Down ? _unit.y : _unit.x), 1);
            } else if (std::find_if(keyToDirection.begin(), keyToDirection.end(), findKey) != keyToDirection.end()) {
                _wichedDirection = std::find_if(keyToDirection.begin(), keyToDirection.end(), findKey)->second;
            }
        }
    }
}

void solarfox::SolarFox::updateEnemies()
{
    for (auto &enemy : _enemies) {
        if (!enemy->shouldMove()) {
            continue;
        }
        auto unitMove = enemy->getUnitMove();
        float speed = 3.5f - (0.125 * _level);
        float x = (unitMove.x * speed) == 0 ? 0 : ((10 * _unit.x) / (unitMove.x * speed)) / (1.0f / _displayer->getDeltaTime());
        float y = (unitMove.y * speed) == 0 ? 0 : ((10 * _unit.y) / (unitMove.y * speed)) / (1.0f / _displayer->getDeltaTime());
        _displayer->log() << "Moving by: " << arcade::data::Vector2f{x, y} << std::endl;
        enemy->getSprite()->move(x, y);
        enemy->update();
        if (enemy->shouldShot()) {
            auto d = enemy->getDirection();
            auto s = (d <= solarfox::direction::Going_Down ? _mapSize.y : _mapSize.x);
            auto u = (d <= solarfox::direction::Going_Down ? _unit.y : _unit.x);
            auto p = enemy->getSprite()->getPosition();
            auto r = findUnitCube(p);
            p.x = r.left + (r.width / 2);
            p.y = r.top  + (r.height / 2);
            createBullet(false, p, d, (s * 0.65f) * u, 3 - (0.1 * _level));
        }
    }
}

bool solarfox::SolarFox::updateBullets()
{
    auto moveBullets = [&](std::vector<std::unique_ptr<solarfox::Bullet>> &bullets) {
        for (auto itBullet = bullets.begin(); itBullet != bullets.end(); ++itBullet) {
            auto &bullet = *itBullet;
            auto unitMove = bullet->getUnitMove();
            float speed = bullet->getSpeed();
            float x = (unitMove.x * speed) == 0 ? 0 : ((10 * _unit.x) / (unitMove.x * speed)) / (1.0f / _displayer->getDeltaTime());
            float y = (unitMove.y * speed) == 0 ? 0 : ((10 * _unit.y) / (unitMove.y * speed)) / (1.0f / _displayer->getDeltaTime());
            bullet->getSprite()->move({x, y});
            if (bullet->shouldDie()) {
                bullets.erase(itBullet);
                --itBullet;
            }
        }
    };
    moveBullets(_pbullets);
    moveBullets(_ebullets);
    static const float ajustement = 0.01f;
    for (auto itPbullet = _pbullets.begin(); itPbullet != _pbullets.end(); ++itPbullet) {
        auto &pbullet = *itPbullet;
        auto pbbound = pbullet->getSprite()->getGlobalBounds();
        pbbound.left += ajustement;
        pbbound.top += ajustement;
        pbbound.width -= ajustement * 2;
        pbbound.height -= ajustement * 2;
        auto itEbullet = std::find_if(_ebullets.begin(), _ebullets.end(),
                            [&pbbound](auto &ebullet) {
                                return arcade::isOverlap(pbbound, ebullet->getSprite()->getGlobalBounds());
                            });
        if (itEbullet != _ebullets.end()) {
            _ebullets.erase(itEbullet);
            _pbullets.erase(itPbullet);
            --itPbullet;
            continue;
        }
        auto itEnemy = std::find_if(_enemies.begin(), _enemies.end(),
                            [&pbbound](auto &e) {
                                return arcade::isOverlap(pbbound, e->getSprite()->getGlobalBounds());
                            });
        if (itEnemy != _enemies.end()) {
            (*itEnemy)->shot();
            _pbullets.erase(itPbullet);
            --itPbullet;
            continue;
        }
        auto itC = std::find_if(_collectables.begin(), _collectables.end(),
                            [&pbbound](auto &c) {
                                return arcade::isOverlap(pbbound, c->getGlobalBounds());
                            });
        if (itC != _collectables.end()) {
            _score += 10 * _level;
            _scoreText->setText("Score: " + std::to_string(_score));
            _collectables.erase(itC);
            _pbullets.erase(itPbullet);
            --itPbullet;
            if (_collectables.empty()) {
                _level += 1;
                if (_level == 5) {
                    return true;
                }
                loadLevel();
                return false;
            }
            continue;
        }
    }
    auto pbounds = _player->getGlobalBounds();
    pbounds.left += ajustement;
    pbounds.top += ajustement;
    pbounds.width -= ajustement * 2;
    pbounds.height -= ajustement * 2;
    auto itEbullet = std::find_if(_ebullets.begin(), _ebullets.end(),
                            [&pbounds](auto &ebullet) {
                                return arcade::isOverlap(pbounds, ebullet->getSprite()->getGlobalBounds());
                            });
    if (itEbullet != _ebullets.end()) {
        _ebullets.erase(itEbullet);
        return true;
    }
    return false;
}

bool solarfox::SolarFox::updatePlayer()
{
    float speed = 3.5f;
    float speedBoost = _playerDirection == _wichedDirection ? 1.75f : 1;
    if (_wichedDirection != direction::No_Direction && _playerDirection != _wichedDirection) {
        if ((_playerDirection <= direction::Going_Down && _wichedDirection <= direction::Going_Down)
        || (_playerDirection > direction::Going_Down && _wichedDirection > direction::Going_Down)) {
            _wichedDirection = direction::No_Direction;
        } else {
            auto pos = _player->getPosition();
            auto inUnit = findUnitCube(pos);
            float diff = pos.x - inUnit.left;
            if ((0 + (inUnit.width * 0.15f)) <= diff && diff <= (inUnit.width - (inUnit.width * 0.15f))) {
                _player->setPosition({inUnit.left + (inUnit.width / 2), inUnit.top + (inUnit.height / 2)});
                _playerDirection = _wichedDirection;
                _player->setRotation(findRotation(_playerDirection));
                _wichedDirection = direction::No_Direction;
            }
        }
    }
    arcade::data::Vector2f directionUnit;
    directionUnit.x = (_playerDirection >  direction::Going_Down ? -1 + (2 * (_playerDirection - 2)) : 0);
    directionUnit.y = (_playerDirection <= direction::Going_Down ? -1 + (2 * _playerDirection) : 0);
    float x = (directionUnit.x * speed) == 0 ? 0 : ((10 * _unit.x) / (directionUnit.x * speed)) / (1.0f / _displayer->getDeltaTime());
    float y = (directionUnit.y * speed) == 0 ? 0 : ((10 * _unit.y) / (directionUnit.y * speed)) / (1.0f / _displayer->getDeltaTime());
    _player->move(x * speedBoost, y * speedBoost);

    auto pbounds = _player->getGlobalBounds();
    static const float ajustement = 0.01f;
    pbounds.left += ajustement;
    pbounds.top += ajustement;
    pbounds.width -= ajustement * 2;
    pbounds.height -= ajustement * 2;
    {
        auto it = std::find_if(_walls.begin(), _walls.end(),
                                [&pbounds](auto &w) {
                                    return arcade::isOverlap(pbounds, w->getGlobalBounds());
                                });
        if (it != _walls.end()) {
            return true;
        }
    }
    {
        auto it = std::find_if(_enemies.begin(), _enemies.end(),
                                [&pbounds](auto &e) {
                                    return arcade::isOverlap(pbounds, e->getSprite()->getGlobalBounds());
                                });
        if (it != _enemies.end()) {
            return true;
        }
    }
    {
        auto it = std::find_if(_collectables.begin(), _collectables.end(),
                                [&pbounds](auto &c) {
                                    return arcade::isOverlap(pbounds, c->getGlobalBounds());
                                });
        if (it != _collectables.end()) {
            _score += 10 * _level;
            _scoreText->setText("Score: " + std::to_string(_score));
            _collectables.erase(it);
            if (_collectables.empty()) {
                _level += 1;
                if (_level == 5) {
                    return true;
                }
                loadLevel();
                return false;
            }
        }
    }
    return false;
}

void solarfox::SolarFox::draw()
{
    auto t = getTimePassed();
    t = 3 - t;
    if (t > 0) {
        int v = static_cast<int>(t);
        _delayText->setText("--- " + std::to_string(v) + " ---");
        _delayText->setColor(v == 3 ?   arcade::data::Color::Red :
                            v == 2 ?    arcade::data::Color::Red :
                            v == 1 ?    arcade::data::Color::Yellow :
                                        arcade::data::Color::Green);
        _displayer->draw(_delayText);
    }
    for (auto &w : _walls) {
        _displayer->draw(w);
    }
    for (auto &c : _collectables) {
        _displayer->draw(c);
    }
    for (auto &enemy : _enemies) {
        _displayer->draw(enemy->getSprite());
    }
    _displayer->draw(_player);
    for (auto &bullet : _pbullets) {
        _displayer->draw(bullet->getSprite());
    }
    for (auto &bullet : _ebullets) {
        _displayer->draw(bullet->getSprite());
    }
    _displayer->draw(_lvlText);
    _displayer->draw(_scoreText);
}