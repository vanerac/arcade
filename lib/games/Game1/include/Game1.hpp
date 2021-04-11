/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Game1
*/

#ifndef GAME1_HPP_
#define GAME1_HPP_

#include "Games.hpp"
#include <chrono>

class Game1 : public arcade::games::IGame {
    public:
        Game1();
        ~Game1();

        void init(std::shared_ptr<arcade::displayer::IDisplay> &disp) override; // maybe call it reloadDisplayer and create a second func initGame which just set pos lives and etc
        // void restart() override;
        arcade::games::GameStatus update() override; // return enum game state
        //GameStatus update() override; // return enum game state
        void stop() override;
        void restart() override {};
        unsigned int getScore() const override;
        void create_snake(arcade::data::Vector2f pos, bool isFirstCell);
        void createBlock(arcade::data::Vector2f pos, bool isApple);
        void snakeMoveUP();
        void snakeMoveDOWN();
        void snakeMoveLEFT();
        void snakeMoveRIGHT();
        void getPosSnake();
        void restartClock();
        double getElapsedTime();
        void automaticMove();

    protected:
    private:
        std::shared_ptr<arcade::displayer::IDisplay> _displayer;
        std::unique_ptr<arcade::displayer::IText> score;
        std::unique_ptr<arcade::displayer::IText> intScore;
        std::vector<std::string> _map_logo;
        std::vector<arcade::data::Vector2f> posSnake;
        std::vector<std::vector<int>> map;
        std::vector<std::vector<int>> snake;
        std::unique_ptr<arcade::displayer::ISprite> _logo;
        std::vector<std::unique_ptr<arcade::displayer::ISprite>> _player;
        std::unique_ptr<arcade::displayer::ISprite> _apple;
        arcade::data::FloatRect _applePos;
        std::vector<std::unique_ptr<arcade::displayer::ISprite>> _blocks;
        arcade::data::Vector2f _unit;
        arcade::data::Vector2f _unit_snake;
        arcade::data::KeyCode direction;
        std::chrono::time_point<std::chrono::high_resolution_clock> _clock = std::chrono::high_resolution_clock::now();
        double automaticMoveTimer = 0.8;
        arcade::data::Vector2u winSize;
        int totScore = 0;
};

#endif /* !GAME1_HPP_ */