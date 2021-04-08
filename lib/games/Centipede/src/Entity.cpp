/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** Entity.cpp.c file
*/

#include "../include/Entities.hpp"

Entity::Entity(int health)
{
    this->health = health;
    this->setPosition(0, 0);
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
    return this->sprite;
}

// &&
void Entity::setSprite(std::unique_ptr<arcade::displayer::ISprite> sprite)
{
    this->sprite = std::move(sprite);
}

void Entity::draw(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
}

bool Entity::does_collide(Entity *target)
{
    return arcade::isOverlap(this->getSprite()->getGlobalBounds(),
        target->getSprite()->getGlobalBounds());
}


void Entity::move()
{
    // todo update position
    // todo update sprite position
}

orientation Entity::getOrientation() const
{
    return this->orientation;
}

void Entity::setOrientation(enum orientation newOrientation)
{
    this->orientation = newOrientation;
}

void Entity::setVecocity(arcade::data::Vector2f velocity)
{
    this->velocity = velocity;
}

arcade::data::Vector2f Entity::getVecocity() const
{
    return this->velocity;
}
