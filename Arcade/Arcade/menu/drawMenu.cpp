/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** drawMenu
*/

#include "Arcade.hpp"

void arcade::Arcade::menuLoadDisplayer()
{
    std::string font{"ressources/font.ttf"};
    _menuQuitText = _displayer->createText("Quit");
    _menuQuitText->setFont(font);
    _menuQuitText->setPosition(_menuQuitText->getPosition().move(0, 1));

    auto winSize = _displayer->getWindowSize();
    const int yOffset = 1;
    int characterSize = isOptions(_displayer, SET_CHARACTER_SIZE) ? 20 : 1;
    int yStart = winSize.y / 2;
    yStart -= ((_galibsPath.size() / 2) * characterSize) + ((_galibsPath.size() / 2) * yOffset);
    yStart += ((_galibsPath.size() % 2) * (yOffset / 2));
    yStart -= ((_galibsPath.size() % 2 == 0) * (characterSize / 2));
    arcade::data::Vector2f pos{static_cast<float>(winSize.x / 2), static_cast<float>(yStart)};
    arcade::data::Vector2f origin{0, 0};

    _menuGamesListText.clear();
    for (unsigned int i = 0; i < _galibsPath.size(); ++i, pos.move(0, yOffset + characterSize)) {
        std::string game = _galibsPath[i];
        std::size_t it = game.find_last_of('/');
        if (it != std::string::npos && ++it < game.size()) {
            game = game.substr(it);
        }
        _menuGamesListText.push_back(_displayer->createText(game));
        auto &text = _menuGamesListText[i];
        text->setCharacterSize(characterSize);
        text->setFont(font);
        origin.x = text->getLocalBounds().width / 2;
        text->setOrigin(origin);
        text->setPosition(pos);
    }

    _pacman = _displayer->createSprite("ressources/pacman.png", {"PAC\r","MA\rN"}, arcade::data::Vector2f{0.1, 0.1});
    auto b = _pacman->getLocalBounds();
    _pacman->setOrigin(b.width / 2);
    _pacman->setColor({}, {{arcade::data::Color::Red, arcade::data::Color::Yellow}, {arcade::data::Color::Blue, arcade::data::Color::Green}});
    _pacman->setPosition(_displayer->getWindowSize().x / 2);
}

void arcade::Arcade::menuInitElems()
{
}

void arcade::Arcade::drawMenu()
{
    if (!_displayer) {
        return;
    }
    _displayer->clearWindow();
    // auto t = _displayer->getDeltaTime();
    // _displayer->log() << "[" << t << ", " << (1.0f / t) << "]" << std::endl;
    _menuQuitText->setPosition(_menuQuitText->getPosition().move(_displayer->scaleMoveX(10), 0));
    // _menuQuitText->setPosition(_menuQuitText->getPosition().move(50 * _displayer->getDeltaTime(), 0));
    _displayer->draw(_menuQuitText);
    for (auto &text : _menuGamesListText) {
        _displayer->draw(text);
    }
    // _pacman->move(0, _displayer->scaleMoveY(3));
    // _pacman->rotate(90);
    _displayer->draw(_pacman);
}