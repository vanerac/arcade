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

void Game1::init(std::unique_ptr<arcade::displayer::IDisplay> &disp)
{
    (void)disp;
    std::cout << "Init Game1" << std::endl;
}
void Game1::update()
{
    std::cout << "Update Game1" << std::endl;
}

void Game1::stop()
{
    std::cout << "Stop Game1" << std::endl;
}
