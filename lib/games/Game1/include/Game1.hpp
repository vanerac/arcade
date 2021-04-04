/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#ifndef GAME1_HPP_
#define GAME1_HPP_

#include "Games.hpp"

class Game1 : public arcade::games::IGame {
    public:
        Game1();
        ~Game1();

        void init(std::unique_ptr<arcade::displayer::IDisplay> &disp) override;
        void update() override;
        void stop() override;

    protected:
    private:
};

#endif /* !GAME1_HPP_ */
