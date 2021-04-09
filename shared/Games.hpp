/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Games
*/

#ifndef GAMES_HPP_
#define GAMES_HPP_

#include "Displayer.hpp"

enum GameStatus {
    PLAYING,
    GAME_ENDED,
};
namespace arcade
{    namespace games
    {
        #define GAMES_ENTRY_POINT       entry_point

        class IGame {
            public:
                virtual void init(std::shared_ptr<arcade::displayer::IDisplay> &disp) = 0;
                virtual GameStatus update() = 0;
                virtual void stop() = 0;

        };
    } // namespace games
} // namespace arcade

#endif /* !GAMES_HPP_ */
