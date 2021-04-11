/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include "ArcErrors.hpp"

arcade::Arcade::Arcade()
{
}

arcade::Arcade::~Arcade()
{
    if (_displayer) {
        _displayer->stop();
    }
}

std::vector<std::string> &arcade::Arcade::getGrlibsPath()
{
    return _grlibsPath;
}

std::vector<std::string> &arcade::Arcade::getGalibsPath()
{
    return _galibsPath;
}

int arcade::Arcade::run()
{
    if (!_grlibsPath.size() || !_galibsPath.size()) {
        throw arcade::errors::LibError("Not enought libs.");
    }
    setGrLib(0);
    _displayer->restartClock();
    while (_status != ArcadeStatus::QUITTING) {
        handleEvents();
        if (_status == ArcadeStatus::MENU) {
            drawMenu();
        } else if (_status == ArcadeStatus::IN_GAME) {
            _displayer->clearWindow();
            if (_game->update() == arcade::games::GameStatus::GAME_ENDED) {
                goBackToMenu();
            }
        }
        _displayer->display();
    }
    if (_game) {
        _game->stop();
    }
    _displayer->stop();
    return 0;
}

void arcade::Arcade::handleEvents()
{
    auto events = _displayer->getEvents();

    for (auto &event : events) {
        if (event.type == arcade::data::EventType::WINDOW_CLOSED
        || (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::ESCAPE)) {
            if (_status == ArcadeStatus::IN_GAME) {
                if (_game) {
                    _game->stop();
                }
                _status = ArcadeStatus::MENU;
            } else {
                _status = ArcadeStatus::QUITTING;
            }
        } else if (event.type == arcade::data::EventType::KEY_PRESSED) {
            if (event.key == '/') {
                setGrLib(-1);
            } else if (event.key == '*') {
                setGrLib(1);
            } else if (_status == ArcadeStatus::IN_GAME && event.key == '8') {
                setGaLib(-1);
            } else if (_status == ArcadeStatus::IN_GAME && event.key == '9') {
                setGaLib(1);
            } else if (_status == ArcadeStatus::IN_GAME && event.key == '-') {
                
                _game->restart();
            }
        }
    }
}