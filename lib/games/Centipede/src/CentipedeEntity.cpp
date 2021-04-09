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
        _tiles.push_back(tmp);
    }
    this->pos.x = 1;
    this->pos.y = 1;
    orientation = RIGHT;
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

void CentipedeEntity::setTiles(const std::vector<Entity *> &tiles)
{
    this->_tiles = tiles;
}

std::vector<Entity *> CentipedeEntity::getTiles() const
{
    return this->_tiles;
}

void CentipedeEntity::move()
{
    this->velocity = 1.0f / this->_tiles.size();
    Position previous = _tiles[0]->getPosition();
    Position buffer = {};
    enum orientation prevOrientation = _tiles[0]->getOrientation();
    enum orientation bufferOrientation;

    for (auto tile : _tiles) {
        buffer = tile->getPosition();
        bufferOrientation = tile->getOrientation();
        tile->setVelocity(1.0f / this->_tiles.size());
        tile->setPosition(previous.x, previous.y);
        tile->setOrientation(prevOrientation);
        tile->move();
        previous = buffer;
        prevOrientation = bufferOrientation;
    }
}

void CentipedeEntity::draw(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    SpriteManager spriteManager(disp, 0); // todo use current level
    int index = 0;
    for (auto body : _tiles) {
        auto orientation = body->getOrientation();
        if (!body->getSprite()) {
            body->setSprite(
                index != 0 ? spriteManager.getCentipedeBody(orientation) :
                    spriteManager.getCentipedeHead(orientation));
            body->getSprite()->setPosition(
                arcade::data::Vector2f(body->getPosition().x,
                    body->getPosition().y));
        }
        body->draw(disp);
        ++index;
    }
}
