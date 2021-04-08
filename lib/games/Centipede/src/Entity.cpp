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
