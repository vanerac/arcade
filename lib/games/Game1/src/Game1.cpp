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
    direction = arcade::data::KeyCode::RIGHT;
    map = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    _map_logo = {"##     #   #####   #####   #####   #        ######   ##### ",  
                 "# #    #     #     #    #  #    #  #        #        #    #",
                 "#  #   #     #     #####   #####   #        ####     ##### ",
                 "#   #  #     #     #    #  #    #  #        #        ###   ",
                 "#    # #     #     #    #  #    #  #        #        #  #  ",
                 "#     ##   #####   #####   #####   ######   ######   #   # "};
}

Game1::~Game1()
{
}

void Game1::createBlock(arcade::data::Vector2f pos, bool isApple)
{
    std::string blockPath;
    std::vector<std::string> blockAscii;

    if (isApple == true){
        blockPath = {"ressources/picture.bmp"};
        blockAscii = {"oo", "oo"};
        _apple = _displayer->createSprite(blockPath, blockAscii, {0.08f, 0.08});
        _apple->setPosition(pos);
    } else {
        blockPath = {"ressources/block.bmp"};
        blockAscii = {"##", "##"};
        _blocks.push_back(_displayer->createSprite(blockPath, blockAscii, {0.08f, 0.08}));
        auto &b = _blocks[_blocks.size() - 1];
        b->setPosition(pos);
    }
}

void Game1::create_snake(arcade::data::Vector2f pos, bool isFirstCell)
{
    std::string snake_path;

    //if (isFirstCell == true)
    //   snake_path = {"ressources/green_round_new.png"};
    //else 
        snake_path = {"ressources/red_round.png"};

    std::vector<std::string> snake_ascii = {"xx", "xx"};
    getPosSnake();

    if (isFirstCell != true) {
        if (direction == arcade::data::KeyCode::UP){
            pos.x = posSnake[posSnake.size() - 1].x;
            pos.y = posSnake[posSnake.size() - 1].y + _unit.y;
        } else if (direction == arcade::data::KeyCode::DOWN) {
            pos.x = posSnake[posSnake.size() - 1].x;
            pos.y = posSnake[posSnake.size() - 1].y - _unit.y;
        } else if (direction == arcade::data::KeyCode::LEFT) {
            pos.x = posSnake[posSnake.size() - 1].x + _unit.x;
            pos.y = posSnake[posSnake.size() - 1].y;
        } else if (direction == arcade::data::KeyCode::RIGHT) {
            pos.x = posSnake[posSnake.size() - 1].x - _unit.x;
            pos.y = posSnake[posSnake.size() - 1].y;
        }
    }

    _player.push_back(_displayer->createSprite(snake_path, snake_ascii, {0.08f, 0.08f}));
    auto &b = _player[_player.size() - 1];
    b->setPosition(pos);
}

void Game1::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    this->_displayer = disp;

    //this->_tmp = _displayer->createText("Hello World");
    //this->_tmp->setCharacterSize(20);
    //this->_tmp->setFont("ressources/font.ttf");
    this->_logo = _displayer->createSprite("./ressources/nibbler_logo.png", _map_logo, {0.4, 0.4});

    auto winSize = _displayer->getWindowSize();
    _logo->setPosition({winSize.x * 0.50f, winSize.y * 0.02f});
    _logo->setOrigin({_logo->getLocalBounds().width / 2, 0});
    this->_displayer->log() << "Init Game1" << std::endl;

    _blocks.clear();
    snake.clear();

    createBlock({0, 0}, false);
    _unit.x = _blocks[0]->getGlobalBounds().width + 0.02f;
    _unit.y = _blocks[0]->getGlobalBounds().height + 0.02f;
    _player.clear();
    _blocks.clear();

    arcade::data::Vector2f initPos{winSize.x * 0.40f, winSize.y * 0.17f};

    arcade::data::Vector2f pos{initPos};
    arcade::data::Vector2f ypos{initPos};
    for (auto &line : map) {
        for (auto cell : line) {
            if (cell) {
                createBlock(pos, false);
            }
            pos.move(_unit.x);
        }
        ypos.move(0, _unit.y);
        pos = ypos;
    }
    arcade::data::Vector2f initPosSnake{initPos.x + _unit.x, initPos.y + ((map.size() - 2) * _unit.y)};
    create_snake(initPosSnake, true);
    //create_snake(initPosSnake, false);
    //create_snake(initPosSnake, false);
    //create_snake(initPosSnake, false);
    int finalPos = 0;
    for (finalPos = std::rand() % (map.size() * map[0].size());
            map[finalPos % map.size()][finalPos / map.size()];
            finalPos = std::rand() % (map.size() * map[0].size()));
    createBlock(initPos + arcade::data::Vector2f{(finalPos / map.size()) * _unit.x, (finalPos % map.size()) * _unit.y}, true);
}

void Game1::snakeMoveRIGHT()
{
    posSnake.clear();
    int i = -1;

    getPosSnake();

    for (auto &b : _player) {
        if (b == _player[0])
            b->move(_unit.x, 0);
        else
            b->setPosition(posSnake[i]);
        i++;
    }
}

void Game1::snakeMoveLEFT()
{
    posSnake.clear();
    int i = -1;

    getPosSnake();

    for (auto &b : _player) {
        if (b == _player[0])
            b->move(-_unit.x, 0);
        else
            b->setPosition(posSnake[i]);
        i++;
    }
}

void Game1::snakeMoveDOWN()
{
    posSnake.clear();
    int i = -1;

    getPosSnake();

    for (auto &b : _player) {
        if (b == _player[0])
            b->move(0, _unit.y);
        else
            b->setPosition(posSnake[i]);
        i++;
    }
}

void Game1::snakeMoveUP()
{
    posSnake.clear();
    int i = -1;

    getPosSnake();

    for (auto &b : _player) {
        if (b == _player[0])
            b->move(0, -_unit.y);
        else
            b->setPosition(posSnake[i]);
        i++;
    }
}

void Game1::getPosSnake()
{
    posSnake.clear();

    for (auto &b : _player){
        posSnake.push_back(b->getPosition());
    }
}

void Game1::restartClock()
{
    _clock = std::chrono::high_resolution_clock::now();
}

double Game1::getElapsedTime()
{
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>
            (std::chrono::high_resolution_clock::now() - _clock).count();
}

void Game1::automaticMove()
{
    if (direction == arcade::data::KeyCode::UP)
        snakeMoveUP();
    if (direction == arcade::data::KeyCode::LEFT)
        snakeMoveLEFT();
    if (direction == arcade::data::KeyCode::RIGHT)
        snakeMoveRIGHT();
    if (direction == arcade::data::KeyCode::DOWN)
        snakeMoveDOWN();
}

void Game1::update()
{
    //this->_displayer->draw(_tmp);
    // gerer les inputs
    // move player
    // Detecter collision
    //auto playerbounds = _player[0]->getGlobalBounds();
    //auto it = std::find_if(_blocks.begin(), _blocks.end(),
    //                [&playerbounds](auto &block) {
    //                    return arcade::isOverlap(block->getGlobalBounds(), playerbounds);
    //                });
    //// _player->move(_unit.x, 0);
    //if (it != _blocks.end()) {
    //    std::cout << "collision" << std::endl;
    //    // There is collision so lost
    //} else if (arcade::isOverlap(playerbounds, _apple->getGlobalBounds())) {
    //    std::cout << "apple" << std::endl;
    //    // You won a point
    //}
    getPosSnake();

    float adjustment = 0.01;
    auto pbounds = _player[0]->getGlobalBounds();
    auto abounds = _apple->getGlobalBounds();

    //abounds.left += adjustment;
    //abounds.top += adjustment;
    //abounds.width += adjustment * 2;
    //abounds.height += adjustment * 2;
//
    //pbounds.left += adjustment;
    //pbounds.top += adjustment;
    pbounds.width -= adjustment * 2;
    pbounds.height -= adjustment * 2;

    if (arcade::isOverlap(pbounds, abounds)){
        this->_displayer->log() << "APPLE" << std::endl;
        create_snake({0, 0}, false);
        int finalPos = 0;
        for (finalPos = std::rand() % (map.size() * map[0].size());
                map[finalPos % map.size()][finalPos / map.size()];
                finalPos = std::rand() % (map.size() * map[0].size()));
        auto winSize = _displayer->getWindowSize();
        arcade::data::Vector2f initPos{winSize.x * 0.40f, winSize.y * 0.17f};
        createBlock(initPos + arcade::data::Vector2f{(finalPos / map.size()) * _unit.x, (finalPos % map.size()) * _unit.y}, true);
    }
    else {
        for (auto &b : _blocks) {
            //_displayer->log() << " Block: pos[" << b->getGlobalBounds().left << ", " << b->getGlobalBounds().top << "] - size[" << b->getGlobalBounds().width << ", " << b->getGlobalBounds().height << "]" << std::endl;
            //_displayer->log() << "Player: pos[" << pbounds.left << ", " << pbounds.top << "] - size[" << pbounds.width << ", " << pbounds.height << "]" << std::endl;
            if (arcade::isOverlap(b->getGlobalBounds(), pbounds)){
                this->_displayer->log() << "HITED" << std::endl;
            }
        }
    }

    if (getElapsedTime() > automaticMoveTimer){
        automaticMove();
        this->_displayer->log() << automaticMoveTimer << std::endl;
        if (automaticMoveTimer >= 0.3)
            automaticMoveTimer -= 0.01;
        restartClock();
    }

    auto events = _displayer->getEvents();
    for (auto &event : events) {
        if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::UP)
            direction = arcade::data::KeyCode::UP;
        if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::LEFT)
            direction = arcade::data::KeyCode::LEFT;
        if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::RIGHT)
            direction = arcade::data::KeyCode::RIGHT;
        if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::DOWN)
            direction = arcade::data::KeyCode::DOWN;
    }
    this->_displayer->draw(_logo);
    for (auto &b : _blocks) {
        _displayer->draw(b);
    }

    _displayer->draw(_apple);
    //arcade::data::Vector2f initPosSnake{_displayer->getWindowSize().x * 0.40f + _unit.x, _displayer->getWindowSize().y * 0.89f};
    //initPosSnake.x += _unit.x;
    //create_snake(initPosSnake);

    for (auto &b : _player) {
        _displayer->draw(b);
    }
}

void Game1::stop()
{
    this->_displayer->log() << "Stop Game1" << std::endl;
}