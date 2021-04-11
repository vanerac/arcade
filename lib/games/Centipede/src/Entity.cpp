/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** Entity.cpp.c file
*/

#include "../include/Entities.hpp"
#include <iostream>

Entity::Entity(int health)
{
    this->health = health;
    this->setPosition(0, 0);
    this->_orientation = STATIC;
}

Entity::~Entity()
{
}

void Entity::setPosition(int new_x, int new_y)
{
    this->pos.x = new_x;
    this->pos.y = new_y;
}

struct Position Entity::getPosition() const
{
    return this->pos;
}

void Entity::setHealth(int health)
{
    this->health = health;
}

int Entity::getHealth() const
{
    return this->health;
}

std::unique_ptr<arcade::displayer::ISprite> &Entity::getSprite()
{
    return this->_sprite;
}

// &&
void Entity::setSprite(std::unique_ptr<arcade::displayer::ISprite> sprite)
{
    this->_sprite = std::move(sprite);
}

void Entity::draw(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    disp->draw(this->getSprite());
}

bool Entity::does_collide(std::unique_ptr<Entity> &target)
{
    auto &thisSprite = this->getSprite();
    auto &targetSprite = target->getSprite();

    if (!(targetSprite))
        return false;
    if (!(thisSprite))
        return false;

    return arcade::isOverlap((thisSprite)->getGlobalBounds(),
        (targetSprite)->getGlobalBounds());
}

void Entity::move()
{
    switch (_orientation) {
    // todo use delta
    case UP:
        std::cout << "up" << std::endl;
        this->setPosition(getPosition().x, getPosition().y - getVelocity());
        break;
    case RIGHT:
        std::cout << "right" << std::endl;
        this->setPosition(getPosition().x + getVelocity(), getPosition().y);
        break;
    case RIGHT_DOWN:
        std::cout << "right down" << std::endl;
        this->setPosition(getPosition().x + getVelocity(),
            getPosition().y + getVelocity());
        break;
    case LEFT:
        std::cout << "left" << std::endl;
        this->setPosition(getPosition().x - getVelocity(), getPosition().y);
        break;
    case LEFT_DOWN:
        std::cout << "left down" << std::endl;
        this->setPosition(this->getPosition().x - getVelocity(),
            this->getPosition().y + getVelocity());
        break;
    case DOWN:
        std::cout << "down" << std::endl;
        this->setPosition(getPosition().x, getPosition().y + getVelocity());
        break;
    case STATIC:
        break;
    }
    this->getSprite()->setPosition(
        arcade::data::Vector2f(getPosition().x, getPosition().y));

    // todo prevent moving beyond window ?
}

orientation Entity::getOrientation() const
{
    return this->_orientation;
}

void Entity::setOrientation(enum orientation newOrientation)
{
    this->_orientation = newOrientation;
}

void Entity::setVelocity(float velocity)
{
    this->velocity = velocity;
}

float Entity::getVelocity() const
{
    return this->velocity;
}
