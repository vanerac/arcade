/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#include <iostream>
#include <algorithm>
#include "Game1.hpp"

Game1::Game1()
{
    _map2 = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
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

void Game1::createBlock(arcade::data::Vector2f pos)
{
    std::string blockPath{"ressources/block.png"};
    std::vector<std::string> blockAscii = {"##", "##"};

    _blocks.push_back(_displayer->createSprite(blockPath, blockAscii, {0.1f, 0.1f}));
    auto &b = _blocks[_blocks.size() - 1];
    b->setPosition(pos);
}

void Game1::create4Block(arcade::data::Vector2f initpos)
{
    createBlock(initpos);
    {
        auto &b = _blocks[_blocks.size() - 1];
        createBlock(b->getPosition() + arcade::data::Vector2f{b->getGlobalBounds().width, 0});
    }
    {
        auto &b = _blocks[_blocks.size() - 1];
        createBlock(b->getPosition() + arcade::data::Vector2f{0, b->getGlobalBounds().height});
    }
    {
        auto &b = _blocks[_blocks.size() - 1];
        createBlock(b->getPosition() + arcade::data::Vector2f{-b->getGlobalBounds().width, 0});
    }
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
    auto winSize = _displayer->getWindowSize();
    _logo->setPosition({winSize.x * 0.50f, winSize.y * 0.02f});
    _logo->setOrigin({_logo->getLocalBounds().width / 2, 0});
    this->_displayer->log() << "Init Game1" << std::endl;

    _blocks.clear();
    createBlock({0, 0});
    _unit.x = _blocks[0]->getGlobalBounds().width;
    _unit.y = _blocks[0]->getGlobalBounds().height;
    _blocks.clear();

    // create4Block({winSize.x * 0.50f, winSize.y * 0.50f});
    arcade::data::Vector2f initPos{winSize.x * 0.40f, winSize.y * 0.15f};
    std::vector<std::vector<int>> map = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    arcade::data::Vector2f pos{initPos};
    arcade::data::Vector2f ypos{initPos};
    for (auto &line : map) {
        for (auto cell : line) {
            if (cell) {
                createBlock(pos);
            }
            pos.move(_unit.x);
        }
        ypos.move(0, _unit.y);
        pos = ypos;
    }
    int finalPos = 0;
    for (finalPos = std::rand() % (map.size() * map[0].size());
            map[finalPos % map.size()][finalPos / map.size()];
            finalPos = std::rand() % (map.size() * map[0].size()));
    // int r = std::rand() % (map.size() * map[0].size());
    createBlock(initPos + arcade::data::Vector2f{(finalPos / map.size()) * _unit.x, (finalPos % map.size()) * _unit.y});
    // const unsigned int mapWidth = 15;
    // const unsigned int mapHeight = 10;
    // create4Block(initPos + arcade::data::Vector2f{2 * _unit.x, 2 * _unit.y});
    
    // arcade::data::Vector2f pos{initPos};
    // for (unsigned int i = 0; i < mapWidth; ++i, createBlock(pos), pos.move(_unit.x));
    // pos = initPos;
    // pos.y += mapHeight * _unit.y;
    // for (unsigned int i = 0; i < mapWidth; ++i, createBlock(pos), pos.move(_unit.x));
    // pos = initPos;
    // for (unsigned int i = 0; i < mapHeight; ++i, createBlock(pos), pos.move(0, _unit.y));
    // pos = initPos;
    // pos.x += mapWidth * _unit.x;
    // for (unsigned int i = 0; i < mapHeight; ++i, createBlock(pos), pos.move(0, _unit.y));
}

void Game1::update()
{
    //this->_displayer->draw(_tmp);
    // gerer les inputs
    // move player
    // Detecter collision
    // auto playerbounds = _player[0]->getGlobalBounds();
    // auto it = std::find_if(_blocks.begin(), _blocks.end(),
    //                 [&playerbounds](auto &block) {
    //                     return arcade::isOverlap(block->getGlobalBounds(), playerbounds);
    //                 });
    // // _player->move(_unit.x, 0);
    // if (it != _blocks.end()) {
    //     // There is collision so lost
    // } else if (arcade::isOverlap(playerbounds, _apple->getGlobalBounds())) {
    //     // You won a point
    // }

    this-> _displayer->draw(_map);
    this->_displayer->draw(_logo);
    this->_displayer->log() << "Update Game1" << std::endl;
    for (auto &b : _blocks) {
        _displayer->draw(b);
    }
}

void Game1::stop()
{
    this->_displayer->log() << "Stop Game1" << std::endl;
}
