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

arcade::data::Vector2f Entity::getPosition() const
{
    return this->_sprite->getPosition();
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
//    this->getSprite()->setPosition(arcade::data::Vector2f(getPosition().x,
//        getPosition().y));
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
        this->setPosition(getPosition().x, getPosition().y - getVelocity());
        this->getSprite()->move(0, -velocity);
        break;
    case RIGHT:
        this->setPosition(getPosition().x + getVelocity(), getPosition().y);
        this->getSprite()->move(velocity, 0);
        break;
    case RIGHT_DOWN:
        this->setPosition(getPosition().x + getVelocity(),
            getPosition().y + getVelocity());
        this->getSprite()->move(velocity, velocity);
        break;
    case LEFT:
        this->setPosition(getPosition().x - getVelocity(), getPosition().y);
        this->getSprite()->move(-velocity, 0);
        break;
    case LEFT_DOWN:
        this->setPosition(this->getPosition().x - getVelocity(),
            this->getPosition().y + getVelocity());
        this->getSprite()->move(-velocity, velocity);
        break;
    case DOWN:

        this->setPosition(getPosition().x, getPosition().y + getVelocity());
        this->getSprite()->move(0, velocity);
        break;
    case STATIC:
        break;
    }
//    this->getSprite()->setPosition(
//        arcade::data::Vector2f(getPosition().x, getPosition().y));
//    getSprite()->move(arcade::data::Vector2f(getPosition().x, getPosition()
//    .y));

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
