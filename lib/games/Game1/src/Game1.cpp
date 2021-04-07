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

std::vector<std::string> Game1::create_nibbler_map()
{
    std::vector<std::string> nibber_map_ncurses;

    nibber_map_ncurses = {"###################################################################",
                          "#                                                                 #",
                          "#                                                                 #",
                          "#     ###########     #     ###########     #     ###########     #",
                          "#     #         #     #                     #     #         #     #",
                          "#     #         #     #                     #     #         #     #",
                          "#     #         #     #     #         #     #     #         #     #",
                          "#     #         #     #     #         #     #     #         #     #",
                          "#     ###########     #     #         #     #     ###########     #",
                          "#                     #     #         #     #                     #",
                          "#                     #     #         #     #                     #",
                          "#     #################     #         #     #################     #",
                          "#                           #         #                           #",
                          "#                                                                 #",                          
                          "#     #################                     #################     #",
                          "#     #                                                     #     #",
                          "#     #                                                     #     #",                          
                          "#     #       ###############         ###############       #     #",                          
                          "#                                                                 #",
                          "#                                                                 #",
                          "#     #################     ###########     #################     #",                          
                          "#                           #         #                           #",
                          "#                           #         #                           #",
                          "#                           #         #                           #",
                          "#                           ###########                           #",
                          "#     ###########     #                     #     ###########     #",
                          "#     #         #     #                     #     #         #     #",
                          "#     #         #     #                     #     #         #     #",
                          "#     #         #     #                     #     #         #     #",
                          "#     #         #     #     ###########     #     #         #     #",
                          "#     ###########     #     #         #     #     ###########     #",
                          "#                     #     #         #     #                     #",
                          "#                     #     #         #     #                     #",
                          "#     #################     ###########     #################     #",
                          "#                                                                 #",
                          "#                                                                 #",
                          "###################################################################"};

    return(nibber_map_ncurses);
}

std::vector<std::string> Game1::create_nibbler_logo()
{
    std::vector<std::string> nibbler_logo;

    nibbler_logo = {"##     #   #####   #####    #####    #         ######    ##### ",  
                    "# #    #     #     #    #   #    #   #         #         #    #",
                    "#  #   #     #     #####    #####    #         ####      ##### ",
                    "#   #  #     #     #    #   #    #   #         #         ###   ",
                    "#    # #     #     #    #   #    #   #         #         #  #  ",
                    "#     ##   #####   #####    #####    ######    ######    #   # "};

    return(nibbler_logo);
}

void Game1::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    this->_displayer = disp;
    std::vector<std::string> _map_ncurses = create_nibbler_map();
    std::vector<std::string> _map_logo = create_nibbler_logo();

    //this->_tmp = _displayer->createText("Hello World");
    //this->_tmp->setCharacterSize(20);
    //this->_tmp->setFont("ressources/font.ttf");
    this->_map = _displayer->createSprite("./ressources/nibbler_map.png", _map_ncurses, {2.2, 2.2});
    this->_logo = _displayer->createSprite("./ressources/nibbler_logo.png", _map_logo, {0.4, 0.4});
    _logo->setPosition({35, 35});
    this->_displayer->log() << "Init Game1" << std::endl;
}

void Game1::update()
{
    //this->_displayer->draw(_tmp);
    this-> _displayer->draw(_map);
    this->_displayer->draw(_logo);
    this->_displayer->log() << "Update Game1" << std::endl;
}

void Game1::stop()
{
    this->_displayer->log() << "Stop Game1" << std::endl;
}
