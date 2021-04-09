/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#include <iostream>
#include "../include/Centipede.hpp"

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
    newLevel();

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
    case arcade::data::UP:
        this->player->setOrientation(UP);
        this->player->setVelocity(1);
        break;
    case arcade::data::DOWN:
        this->player->setOrientation(DOWN);
        this->player->setVelocity(1);
        break;
    case arcade::data::LEFT:
        this->player->setOrientation(LEFT);
        this->player->setVelocity(1);
        break;
    case arcade::data::RIGHT:
        this->player->setOrientation(RIGHT);
        this->player->setVelocity(1);
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
    auto mapLimit = arcade::data::FloatRect(
        this->_displayer->getWindowSize().x,
        this->_displayer->getWindowSize().y);

    for (auto shot : _shots) {
        if (!shot)
            continue;
        // Move & check collision with obstacles & centipedes
        shot->move();
        for (auto centipede : _centipedes) {
            if (centipede->getTiles().empty()) {
                delete centipede;
                continue;
            }
            int index = -1;
            for (auto body : centipede->getTiles()) {
                ++index; // todo too dirty
                if (shot->does_collide(body)) {
                    auto tmp = new Entity(4);
                    tmp->setPosition(body->getPosition().x,
                        body->getPosition().y);
                    tmp->setSprite(
                        spriteManager->getObstacle(tmp->getHealth()));
                    this->_obstacles.push_back(tmp);
                    this->_centipedes.push_back(centipede->splitAt(index));
                    // todo explosion animation ?
                    delete shot;
                    continue;
                } else if (arcade::isOverlap(mapLimit,
                    shot->getSprite()->getGlobalBounds())) {
                    delete shot;
                    continue;
                }
            }
        }
        for (auto obstacle : _obstacles) {
            obstacle->move(); // doesn't move doe -_-
            if (!shot->does_collide(obstacle))
                continue;
            obstacle->setHealth(obstacle->getHealth() - 1);
            obstacle->setSprite(
                spriteManager->getObstacle(obstacle->getHealth()));
            if (obstacle->getHealth() == 0) {
                delete obstacle;
            }
        }
    }

    for (auto centipede : _centipedes) {
        if (centipede->getTiles().empty()) {
            delete centipede;
            continue;
        }
        for (auto body : centipede->getTiles()) {
            if (body->does_collide(this->player)) {
                // todo trigger game over
            }
            for (auto obstacle: _obstacles) {
                if (!obstacle)
                    continue; // todo could be unnecessary
                if (body->does_collide(obstacle) || arcade::isOverlap(mapLimit,
                    body->getSprite()->getGlobalBounds())) {
                    centipede->setOrientation(
                        centipede->getOrientation() == RIGHT ? LEFT_DOWN :
                            RIGHT_DOWN);
                }
            }
        }
        centipede->move();
    }

    // User actions
    auto event = this->_displayer->getEvents();
    handleMovement(event);
    player->move();
    player->setVelocity(0); // todo dont move forever

    if (_centipedes.empty())
        this->newLevel();

    draw();
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
    player->draw(this->_displayer);
}

void Centipede::shoot()
{
    auto shot = new Entity(1);
    shot->setVelocity(1);
    shot->setOrientation(UP);
    shot->setSprite(spriteManager->getShot());
    shot->setPosition(
        player->getPosition().x + player->getSprite()->getLocalBounds().height,
        player->getPosition().y);

    this->_shots.push_back(shot);
}

void Centipede::newLevel()
{
    current_level++;
    for (int i = 0; i < current_level; i++)
        _centipedes.push_back(new CentipedeEntity(current_level + 5));
}

