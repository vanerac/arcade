/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** SpriteManager.cpp.c file
*/

#include "../include/SpriteManager.hpp"

SpriteManager::SpriteManager
(std::shared_ptr<arcade::displayer::IDisplay> &disp, int level)
{
    this->_level = level;
    displayer = disp;
}


SpriteManager::~SpriteManager()
{
}

void SpriteManager::change_level(int level)
{
}

//std::unique_ptr<arcade::displayer::ISprite> SpriteManager::loadCentipedeHeads()
//{
//    std::string ascii = "O";
//    return this->displayer->createSprite();
//}
//
//void SpriteManager::loadCentipedeBodies()
//{
//
//    std::string ascii = "-";
//}
//
//void SpriteManager::loadObstacle()
//{
//    std::string ascii = "X";
//}
//
//void SpriteManager::loadPlayer()
//{
//    std::string ascii = "W";
//}
//
//void SpriteManager::loadShot()
//{
//    std::string ascii = "|";
//}

std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getCentipedeHead(
    orientation
) const
{
    return std::unique_ptr<arcade::displayer::ISprite>();
}



std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getCentipedeBody(
    orientation
) const
{
    return std::unique_ptr<arcade::displayer::ISprite>();
}



std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getObstacle(
    int health
) const
{
    return std::unique_ptr<arcade::displayer::ISprite>();
}



std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getPlayer() const
{
    return std::unique_ptr<arcade::displayer::ISprite>();
}



std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getShot() const
{
    return this->_shot;
}

std::unique_ptr<arcade::displayer::IText> SpriteManager::getText(
    std::string &text
) const
{
    auto tmp = this->displayer->createText();
    tmp->setFont("ressources/8-BIT WONDER.TTF");
    // todo set color
    // todo set Char size
    tmp->setText(text);
    return tmp;
}


