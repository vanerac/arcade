/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#include <iostream>
#include "../include/Centipede.hpp"

Centipede::Centipede()
{
    /*Todo
     * Swawn random collision entities
     * Spawn centipede
     * Spawn Player
     * */
}

Centipede::~Centipede()
{
}


void Centipede::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    // todo only inits structures

    //    _displayer = disp;
    //    _tmp = _displayer->createText("Hello World");
    //    _tmp->setCharacterSize(20);
    //    _tmp->setFont("ressources/font.ttf");
    //    _displayer->log() << "Init Game1" << std::endl;
}

void Centipede::update()
{

    /*Todo
     * Move bullet
     * check centipede hit -> set hit as collider and prev to new head
     * Move centipede -> Follow
     * Check User collision with centipede
     * Get User Actions -> move, shoot
     * */
    _displayer->log() << "Update Game1" << std::endl;
}

void Centipede::stop()
{
    _displayer->log() << "Stop Game1" << std::endl;
}

