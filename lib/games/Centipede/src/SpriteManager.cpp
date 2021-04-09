/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** SpriteManager.cpp.c file
*/

#include "../include/SpriteManager.hpp"

SpriteManager::SpriteManager(
    std::shared_ptr<arcade::displayer::IDisplay> &disp, int level
)
{
    this->_level = level;
    displayer = disp;

    // todo load file
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::change_level(int level)
{
}

std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getCentipedeHead(
    orientation orientation
) const
{

    switch (orientation) {
    case RIGHT:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/head_right.png"), {"X"});
    case RIGHT_DOWN:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/head_right_down.png"), {"X"});
    case LEFT:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/head_left.png"), {"X"});
    case LEFT_DOWN:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/head_left_down.png"), {"X"});
    default:
        return nullptr;
    }
}

std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getCentipedeBody(
    orientation orientation
) const
{
    switch (orientation) {
    case RIGHT:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/body_right.png"), {"x"});

    case RIGHT_DOWN:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/body_down_right.png"), {"x"});
    case LEFT:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/body_left.png"), {"x"});
    case LEFT_DOWN:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/body_down_left.png"), {"x"});
    default:
        return nullptr;
    }
}

std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getObstacle(
    int health
) const
{
    // todo  change ascii sprite
    switch (health) {
    case 4:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/obstacle_4.png"), {"O"});
    case 3:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/obstacle_3.png"), {"O"});
    case 2:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/obstacle_2.png"), {"O"});
    case 1:
        return this->displayer->createSprite(
            std::string("ressorces/Centipede/obstacle_1.png"), {"O"});
    default:
        return nullptr;
    }

    return std::unique_ptr<arcade::displayer::ISprite>();
}

std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getPlayer() const
{
    return this->displayer->createSprite(
        std::string("ressorces/Centipede/player.png"), {"X"});
}

std::unique_ptr<arcade::displayer::ISprite> SpriteManager::getShot() const
{
    return this->displayer->createSprite(
        std::string("ressorces/Centipede/shot.png"), {"|"});
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


