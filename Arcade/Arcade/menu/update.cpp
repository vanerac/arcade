/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** update
*/

#include <algorithm>
#include "Arcade.hpp"

void arcade::Arcade::menuInitElems()
{
}

void arcade::Arcade::drawMenu()
{
    if (!_displayer) {
        return;
    }
    _displayer->clearWindow();
    menuHandleEvents();
    for (auto &box : _menuBoxes) {
        _displayer->draw(box);
    }
    for (auto &text : _menuGamesListText) {
        _displayer->draw(text);
    }
    _displayer->draw(_menuHighScoreText);
    for (auto &text : _menuHighScoresText) {
        _displayer->draw(text);
    }
    for (auto &text : _menuGrListText) {
        _displayer->draw(text);
    }
    _displayer->draw(_menuNewGameText);
    _displayer->draw(_menuAskPlayerNameText);
    _displayer->draw(_menuPlayerNameText);
    for (auto &text : _menuInstructions) {
        _displayer->draw(text);
    }
}

void arcade::Arcade::menuHandleEvents()
{
    auto events = _displayer->getEvents();
    for (auto &event : events) {
        if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::UP) {
            _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::White);
            _menuSelectedGame -= _menuSelectedGame ? 1 : 0;
            _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::Cyan);
            menuSetHighScoresText();
        } else if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::DOWN) {
            _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::White);
            _menuSelectedGame += _menuSelectedGame < _menuGamesListText.size() - 1 ? 1 : 0;
            _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::Cyan);
            menuSetHighScoresText();
        } else if (event.type == arcade::data::MOUSE_PRESSED) {
            auto it = std::find_if(_menuGamesListText.begin(), _menuGamesListText.end(),
                                [&event](auto &text) {
                                    auto b = text->getLocalBounds();
                                    b.left = text->getPosition().x;
                                    b.top = text->getPosition().y;
                                    return arcade::isOverlap(b, event.x, event.y);
                                });
            if (it != _menuGamesListText.end()) {
                if (it - _menuGamesListText.begin() == _menuSelectedGame) {
                    setGaLib(_menuSelectedGame - _gameLoaded);
                    _status = ArcadeStatus::IN_GAME;
                } else {
                    _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::White);
                    _menuSelectedGame = it - _menuGamesListText.begin();
                    _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::Cyan);
                    menuSetHighScoresText();
                }
            }
        } else if (event.type == arcade::data::EventType::KEY_PRESSED &&
        (  (event.key >= 'a' && event.key <= 'z')
        || (event.key >= 'A' && event.key <= 'Z')
        || (event.key >= '0' && event.key <= '9')
        || (event.key == '-' || event.key == '_' || event.keyCode == arcade::data::KeyCode::BACKSPACE))) {
            auto str = _menuPlayerNameText->getText();
            auto it = str.find('_');
            if (event.key == '\a') {
                if (it != 0) {
                    it = (it == std::string::npos ? str.size() : it) - 1;
                    str[it] = '_';
                    _menuPlayerNameText->setText(str);
                }
            } else if (it != std::string::npos) {
                str[it] = event.key;
                _menuPlayerNameText->setText(str);
                ++it;
            }
            _playerName = str.substr(0, it);
        } else if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::ENTER) {
            setGaLib(_menuSelectedGame - _gameLoaded);
            _status = ArcadeStatus::IN_GAME;
        }
    }
}