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

        void init(std::shared_ptr<arcade::displayer::IDisplay> &disp) override; // maybe call it reloadDisplayer and create a second func initGame which just set pos lives and etc
        // void restart() override;
        void update() override; // return enum game state
        void stop() override;
        // int getScore() override; for the arcade to store the score if it is a high score

    protected:
    private:
        std::shared_ptr<arcade::displayer::IDisplay> _displayer;
        std::unique_ptr<arcade::displayer::IText> _tmp;
};

#endif /* !GAME1_HPP_ */
