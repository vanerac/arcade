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
    //    _displayer->log() << "CONSTRUCTOR IN" << std::endl;

    std::cout << "Constructor in" << std::endl;

    player = std::make_unique<Entity>(1);
    this->current_level = 0;
    /*Todo
     * Spawn:
     *  - random collision entities
     *  - centipede
     *  - Player
     * */
    player->setPosition(50, 50);
    newLevel();
    std::cout << "Constructor out" << std::endl;

    //    _displayer->log() << "CONSTRUCTOR OUT" << std::endl;
}

Centipede::~Centipede()
{
}

unsigned int Centipede::getScore() const
{
    return 0;
}

void Centipede::init(std::shared_ptr<arcade::displayer::IDisplay> &disp)
{
    _displayer = disp;
    std::cout << "init in" << std::endl;
    // _displayer->log() << "INIT IN" << std::endl;
    spriteManager = std::make_unique<SpriteManager>(disp, current_level);

    player->setSprite(spriteManager->getPlayer());
    player->setPosition(disp->getWindowSize().x / 2, disp->getWindowSize().y -
        player->getSprite()->getLocalBounds().height);
    for (auto &centipede : _centipedes) {
        for (auto &body : centipede->getTiles()) {
            body->setSprite(
                spriteManager->getCentipedeBody(centipede->getOrientation()));
            body->getSprite()->setPosition(
                arcade::data::Vector2f(disp->getWindowSize().x / 2, 0.0f));
        }
    }

    for (auto &obstacle : _obstacles)
        obstacle->setSprite(spriteManager->getObstacle(obstacle->getHealth()));
    for (auto &shot : _shots)
        shot->setSprite(spriteManager->getShot());
    // _displayer->log() << "INIT OUT" << std::endl;
    // todo display text

}

void Centipede::handleMovement(
    std::vector<arcade::data::Event, std::allocator<arcade::data::Event>> events
)
{
    for (auto event : events) {
        auto type = event.type;

        if (type != arcade::data::KEY_PRESSED)
            return;

        switch (event.keyCode) {
        case arcade::data::UP:
            this->player->setOrientation(UP);
            this->player->setVelocity(player->getVelocity() + 1);
            break;
        case arcade::data::DOWN:
            this->player->setOrientation(DOWN);
            this->player->setVelocity(player->getVelocity() + 1);
            break;
        case arcade::data::LEFT:
            this->player->setOrientation(LEFT);
            this->player->setVelocity(player->getVelocity() + 1);
            break;
        case arcade::data::RIGHT:
            this->player->setOrientation(RIGHT);
            this->player->setVelocity(player->getVelocity() + 1);
            break;
        case arcade::data::SPACE:
            this->shoot();
            break;
        default:
            break;
        }
    }
}

arcade::games::GameStatus Centipede::update()
{
    // _displayer->log() << "Update IN" << std::endl;
    auto mapLimit = arcade::data::FloatRect(
        this->_displayer->getWindowSize().x,
        this->_displayer->getWindowSize().y);

    // for (auto &shot : _shots) {
    for (auto itShot = _shots.begin(); itShot != _shots.end(); ++itShot) {
        auto &shot = *itShot;
        if (!shot)
            continue;
        shot->move();
        for (auto itCentipede = _centipedes.begin();
            itCentipede != _centipedes.end(); ++itCentipede) {
            auto &centipede = *itCentipede;
            if (!centipede)
                continue;
            if (centipede->getTiles().empty()) {
                _centipedes.erase(itCentipede);
                --itCentipede;
                continue;
            }
            int index = -1;
            for (auto &body : centipede->getTiles()) {
                if (!body)
                    continue;
                ++index; // todo too dirty
                if (shot && shot->does_collide(body)) {
                    this->_obstacles.push_back(std::make_unique<Entity>(4));
                    auto &tmp = this->_obstacles[_obstacles.size() - 1];
                    tmp->setPosition(body->getPosition().x,
                        body->getPosition().y);
                    tmp->setSprite(
                        spriteManager->getObstacle(tmp->getHealth()));
                    this->_centipedes.push_back(centipede->splitAt(index));
                    // todo explosion animation ?
                    _shots.erase(itShot);
                    // _displayer->log() << "SHOT DELETED BY CENTIPEDE" << std::endl;
                    --itShot;
                    continue;
                }
            }
            if (shot && !arcade::isOverlap(mapLimit,
                shot->getSprite()->getGlobalBounds())) {
                _shots.erase(itShot);
                // _displayer->log() << "SHOT DELETED BY MAP LIMIT" << std::endl;
                --itShot;
                continue;
            }
        }
        for (auto itObstacle = _obstacles.begin();
            itObstacle != _obstacles.end(); ++itObstacle) {
            auto &obstacle = *itObstacle;
            obstacle->move(); // doesn't move doe -_-
            if (!shot->does_collide(obstacle))
                continue;
            obstacle->setHealth(obstacle->getHealth() - 1);
            obstacle->setSprite(
                spriteManager->getObstacle(obstacle->getHealth()));
            if (obstacle->getHealth() == 0) {
                _obstacles.erase(itObstacle);
                // _displayer->log() << "SHOT DELETED BY OBSTACLE" << std::endl;
                --itObstacle;
            }
        }
    }
    // _displayer->log() << "UPDATE MOVE CENTIPEDE" << std::endl;
    for (auto itCentipede = _centipedes.begin();
        itCentipede != _centipedes.end(); ++itCentipede) {
        auto &centipede = *itCentipede;
        if (!centipede)
            continue;
        if (centipede->getTiles().empty()) {
            _centipedes.erase(itCentipede);
            --itCentipede;
            continue;
        }
        auto &head = centipede->getTiles()[0]; // only head, rest follows
        if (!head)
            continue;
        if (head->does_collide(this->player))
            return arcade::games::GameStatus::GAME_ENDED;

        if (!arcade::isOverlap(mapLimit,
            head->getSprite()->getGlobalBounds())) {
            std::cout << "OUT OF BOUNDS" << std::endl;
            centipede->setOrientation(
                centipede->getOrientation() == RIGHT ? LEFT_DOWN : RIGHT_DOWN);
        }
        for (auto &obstacle: _obstacles) {
            if (obstacle && head->does_collide(obstacle)) {

                centipede->setOrientation(
                    centipede->getOrientation() == RIGHT ? LEFT_DOWN :
                        RIGHT_DOWN);
            }
        }

        centipede->move();
    }

    // _displayer->log() << "UPDATE USER INPUT" << std::endl;
    auto event = this->_displayer->getEvents();
    handleMovement(event);
    player->move();
    player->setVelocity(0);

    if (_centipedes.empty())
        this->newLevel();
    // _displayer->log() << "UPDATE DRAW" << std::endl;
    draw();
    // _displayer->log() << "Update OUT" << std::endl;
    return arcade::games::GameStatus::PLAYING;
}

void Centipede::stop()
{
    // _displayer->log() << "Stop Game1" << std::endl;
}

void Centipede::draw()
{

    // _displayer->log() << "DRAW IN" << std::endl;
    this->_displayer->clearWindow();
    for (auto &centipede : _centipedes)
        centipede->draw(this->_displayer);
    for (auto &obstacles : _obstacles)
        obstacles->draw(this->_displayer);
    for (auto &shot : _shots) {
        if (shot)
            shot->draw(this->_displayer);
    }
    player->draw(this->_displayer);
    // _displayer->log() << "DRAW OUT" << std::endl;
}

void Centipede::shoot()
{
    // _displayer->log() << "SHOT CREATED" << std::endl;
    auto shot = std::make_unique<Entity>(1);
    shot->setVelocity(5);
    shot->setOrientation(UP);
    shot->setSprite(spriteManager->getShot());
    shot->getSprite()->setPosition(arcade::data::Vector2f(
        player->getPosition().x +
            (player->getSprite()->getLocalBounds().width / 2),
        player->getPosition().y -
            player->getSprite()->getLocalBounds().height));

    this->_shots.emplace_back(std::move(shot));
}

void Centipede::newLevel()
{
    current_level++;
    for (int i = 0; i < current_level; i++) {
        auto tmp = std::make_unique<CentipedeEntity>(current_level + 5);
        if (_displayer) {
            // set positions
            tmp->setPosition(_displayer->getWindowSize().x / 2,
                _displayer->getWindowSize().y);
        }
        tmp->setOrientation(i % 2 ? RIGHT : LEFT);
        _centipedes.push_back(std::move(tmp));
    }
}

