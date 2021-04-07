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
        std::vector<std::string> create_nibbler_map();
        std::vector<std::string> create_nibbler_logo();
        // int getScore() override; for the arcade to store the score if it is a high score

    protected:
    private:
        std::shared_ptr<arcade::displayer::IDisplay> _displayer;
        std::unique_ptr<arcade::displayer::IText> _tmp;
        std::unique_ptr<arcade::displayer::ISprite> _map;
        std::unique_ptr<arcade::displayer::ISprite> _logo;
};

#endif /* !GAME1_HPP_ */