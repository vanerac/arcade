/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#include <iostream>
#include "../include/Centipede.hpp"

bool Centipede::does_collide(arcade::data::Rect<float> first,
    arcade::data::Rect<float> second
)
{

    // todo check collision
    return false;
}

Centipede::Centipede()
{

    player = new Entity(1);
    this->current_level = 1;
    /*Todo
     * Spawn:
     *  - random collision entities
     *  - centipede
     *  - Player
     * */

}

Centipede::~Centipede()
{
}

void Centipede::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    _displayer = disp;
    spriteManager = new SpriteManager(disp, current_level);

    player->setSprite(spriteManager->getPlayer());
    for (auto centipede : _centipedes)
        for (auto body : centipede->getTiles())
            body->setSprite(
                spriteManager->getCentipedeBody(centipede->getOrientation()));

    for (auto obstacle : _obstacles)
        obstacle->setSprite(spriteManager->getObstacle(obstacle->getHealth()));
    for (auto shot : _shots)
        shot->setSprite(spriteManager->getShot());

    // todo display text

}

void Centipede::handleMovement(
    std::vector<arcade::data::Event, std::allocator<arcade::data::Event>> eventType
)
{
    auto type = eventType[0].type;

    if (type != arcade::data::KEY_PRESSED)
        return;

    switch (eventType[0].keyCode) {
        // todo movement
    case arcade::data::UP:
        break;
    case arcade::data::DOWN:
        break;
    case arcade::data::LEFT:
        break;
    case arcade::data::RIGHT:
        break;
    case arcade::data::SPACE:
        this->shoot();
        break;
    default:
        return;
    }
}

void Centipede::update()
{
    for (auto shot : _shots) {
        // Move & check collision with obstacles & centipedes
        for (auto centipede : _centipedes) {
            for (auto body : centipede->getTiles()) {
                if (!does_collide(shot->getSprite()->getLocalBounds(),
                    body->getSprite()->getLocalBounds()))
                    continue;
                // todo place obstacle in collision spot
                // todo split
            }
        }
        for (auto obstacle : _obstacles) {
            // check for bounds
            if (!does_collide(shot->getSprite()->getLocalBounds(),
                obstacle->getSprite()->getLocalBounds()))
                continue;
            obstacle->setHealth(obstacle->getHealth() - 1);
            // todo update sprite ?
        }
    }

    for (auto centipede : _centipedes) {
        centipede->move(); // todo centipede move speed depends on size;
        // todo check collisions
    }

    // User actions
    auto event = this->_displayer->getEvents();
    handleMovement(event);

    // todo if no more centipedes, spawn new ones & level++

    _displayer->log() << "Update Game1" << std::endl;
}

void Centipede::stop()
{
    _displayer->log() << "Stop Game1" << std::endl;
}

void Centipede::draw()
{
    this->_displayer->clearWindow();
    for (auto centipede : _centipedes)
        centipede->draw(this->_displayer);
    for (auto obstacles : _obstacles)
        obstacles->draw(this->_displayer);
    for (auto shot : _shots)
        shot->draw(this->_displayer);
    // todo display player

}

void Centipede::shoot()
{
}

