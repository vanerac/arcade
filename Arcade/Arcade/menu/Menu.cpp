/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Menu
*/

#include "Arcade.hpp"

arcade::Menu::Menu()
{
}

arcade::Menu::~Menu()
{
}

void arcade::Menu::loadDisplayer(std::shared_ptr<arcade::displayer::IDisplay> displayer)
{
    _displayer = displayer;
    _quitText = displayer->createText("Quit");
    _quitText->setFont("ressources/font.ttf");
    // for (int i = 0; i < )
}

void arcade::Menu::draw()
{
    if (!_displayer) {
        return;
    }
    _displayer->clear();
    _quitText->setPosition(_quitText->getPosition().move(40000 * _displayer->getDeltaTime()));
    _displayer->draw(_quitText);
}