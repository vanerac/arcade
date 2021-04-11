/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** CentipedeEntity.c file
*/

#include "../include/Centipede.hpp"

CentipedeEntity::CentipedeEntity(int size) : Entity(1)
{

    for (int i = 0; i < size; ++i) {
        // auto tmp = new Entity(1);
        _tiles.push_back(std::make_unique<Entity>(1));
    }
    this->pos.x = 1;
    this->pos.y = 1;
    _orientation = RIGHT;
    this->velocity = 1;
}

CentipedeEntity::~CentipedeEntity()
{
}

std::unique_ptr<CentipedeEntity> CentipedeEntity::splitAt(int tileIndex)
{
    // return t
    std::vector<std::unique_ptr<Entity>> &tiles = getTiles();
    std::vector<std::unique_ptr<Entity>> split_hi;//(tiles.begin(), tiles.begin() + tileIndex);
    split_hi.insert(split_hi.end(), std::make_move_iterator(tiles.begin()),
        std::make_move_iterator(tiles.begin() + tileIndex));
    std::vector<std::unique_ptr<Entity>> split_lo;//(tiles.begin() + tileIndex, tiles.end());
    split_lo.insert(split_lo.end(),
        std::make_move_iterator(tiles.begin() + tileIndex),
        std::make_move_iterator(tiles.end()));
    this->setTiles(std::move(split_hi));
    if (split_lo.empty())
        return nullptr; // todo return empty
    std::unique_ptr<Entity> &v = split_lo.front();
    // if (!v)
    //     return nullptr;
    auto ret = std::make_unique<CentipedeEntity>(1);
    ret->setTiles(std::move(split_lo));
    ret->setPosition(v->getPosition().x, v->getPosition().y);
    // TODO did it shrink ?
    ret->setOrientation(_orientation == RIGHT ? LEFT : RIGHT);
    return ret;
}

void CentipedeEntity::setTiles(std::vector<std::unique_ptr<Entity>> tiles)
{
    this->_tiles = std::move(tiles);
}

std::vector<std::unique_ptr<Entity>> &CentipedeEntity::getTiles()
{
    return this->_tiles;
}

void CentipedeEntity::move()
{
    this->velocity = 1.0f / this->_tiles.size();
    arcade::data::Vector2f previous = _tiles[0]->getPosition();
    arcade::data::Vector2f buffer = {};
    enum orientation prevOrientation = this->getOrientation();
    enum orientation bufferOrientation;

    int i = -1;
    for (auto &tile : _tiles) {
        ++i;
        buffer = tile->getPosition();
        bufferOrientation = tile->getOrientation();

        if (tile != _tiles[0] && tile->getPosition() == previous)
            continue;

        std::cout << i << " " << tile->getPosition() << " ";
        tile->setVelocity(this->_tiles.size() +
            tile->getSprite()->getLocalBounds().width / 2);
        tile->setOrientation(prevOrientation);
        tile->move();

        previous = buffer;
        prevOrientation = bufferOrientation;

        if (bufferOrientation == RIGHT_DOWN) {
            std::cout << "SKRR RIGHT" << std::endl;
            tile->setOrientation(RIGHT);
        } else if (bufferOrientation == LEFT_DOWN) {
            std::cout << "SKRR LEFT" << std::endl;
            tile->setOrientation(LEFT);
        }
    }
    //    if (_tiles[0]->getOrientation() != this->getOrientation())
    this->setOrientation(_tiles[0]->getOrientation());
    if (this->getOrientation() == RIGHT_DOWN) {
        std::cout << "SKRR RIGHT" << std::endl;
        this->setOrientation(RIGHT);
    } else if (this->getOrientation() == LEFT_DOWN) {
        std::cout << "SKRR LEFT" << std::endl;
        this->setOrientation(LEFT);
    }
    std::cout << std::endl;
}

void CentipedeEntity::draw(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    SpriteManager spriteManager(disp, 0);
    int index = 0;
    for (auto &body : _tiles) {
        // todo head sprite
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
