/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#include <iostream>
#include "Game1.hpp"

Game1::Game1()
{
}

Game1::~Game1()
{
}

void Game1::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    _displayer = disp;
    _tmp = _displayer->createText("Hello World");
    _tmp->setCharacterSize(20);
    _tmp->setFont("ressources/font.ttf");
    _displayer->log() << "Init Game1" << std::endl;
}
void Game1::update()
{
    _displayer->draw(_tmp);
    _displayer->log() << "Update Game1" << std::endl;
}

void Game1::stop()
{
    _displayer->log() << "Stop Game1" << std::endl;
}
