/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** CentipedeEntity.c file
*/

#include "../include/Centipede.hpp"
#include "../include/Entities.hpp"

CentipedeEntity::CentipedeEntity(int size) : Entity(1)
{

    for (int i = 0; i < size; ++i) {
        auto tmp = new Entity(1);
        // todo set Sprite
        // todo set position
        _tiles.push_back(tmp);
    }
    this->pos.x = 1;
    this->pos.y = 1;
    orientation = RIGHT; // todo inherit when necessary
}

CentipedeEntity::~CentipedeEntity()
{
}

CentipedeEntity *CentipedeEntity::splitAt(int tileIndex)
{
    // return t
    std::vector<Entity *> tiles = getTiles();
    std::vector<Entity *> split_hi(tiles.begin(), tiles.begin() + tileIndex);
    std::vector<Entity *> split_lo(tiles.begin() + tileIndex, tiles.end());
    this->setTiles(split_hi);
    Entity *v = split_lo.front();
    if (!v)
        return nullptr;
    auto ret = new CentipedeEntity(1);
    ret->setTiles(split_lo);
    ret->setPosition(v->getPosition().x, v->getPosition().y);
    // TODO did it shrink ?
    ret->setOrientation(orientation == RIGHT ? LEFT : RIGHT);
    return ret;
}

void CentipedeEntity::setTiles(const std::vector<Entity *>& tiles)
{
    this->_tiles = tiles;
}

std::vector<Entity *> CentipedeEntity::getTiles() const
{
    return this->_tiles;
}

void CentipedeEntity::move()
{
    this->velocity = this->_tiles.size();
    for (auto tile : _tiles)
        tile->move();
}
