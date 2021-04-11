/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_

#include <memory>
#include "Games.hpp"
#include "Entities.hpp"
#include "SpriteManager.hpp"

class Centipede : public arcade::games::IGame {
    public:
    Centipede();

    ~Centipede();

    void init(std::shared_ptr<arcade::displayer::IDisplay> &disp
    ) override;
    arcade::games::GameStatus update() override;
    void draw();
    void stop() override;
    unsigned int getScore() const override;
    void restart() override {};

    protected:
    private:
    int current_level;
    std::shared_ptr<arcade::displayer::IDisplay> _displayer;
    std::vector<std::unique_ptr<CentipedeEntity>> _centipedes;
    std::vector<std::unique_ptr<Entity>> _obstacles;
    std::unique_ptr<SpriteManager> spriteManager = nullptr;
    std::vector<std::unique_ptr<Entity>> _shots;
    std::unique_ptr<Entity> player = nullptr;

    void shoot();
    void handleMovement(
        std::vector<arcade::data::Event, std::allocator<arcade::data::Event>> events
    );
    void newLevel();
};

#endif /* !GAME1_HPP_ */
