/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include "Games.hpp"
#include "Entities.hpp"
#include "SpriteManager.hpp"

class Centipede : public arcade::games::IGame {
    public:
    Centipede();

    ~Centipede();

    void init(std::shared_ptr<arcade::displayer::IDisplay> &disp
    ) override; // maybe call it reloadDisplayer and create a second func initGame which just set pos lives and etc
    // void restart() override;
    void update() override; // return enum game state
    void draw();
    void stop() override;
    // int getScore() override; for the arcade to store the score if it is a high score
    // BITE

    protected:
    private:
    int current_level;
    std::shared_ptr<arcade::displayer::IDisplay> _displayer;
    std::vector<CentipedeEntity *> _centipedes;
    std::vector<Entity *> _obstacles;
    SpriteManager  *spriteManager = nullptr;
    std::vector<Entity *> _shots;
    Entity *player = nullptr;

    void shoot();
    void handleMovement(
        std::vector<arcade::data::Event, std::allocator<arcade::data::Event>> events
    );
    void newLevel();
};

#endif /* !GAME1_HPP_ */
