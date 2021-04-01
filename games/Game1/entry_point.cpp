/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** entry_point
*/

#include <memory>
#include "Game1.hpp"

extern "C" std::unique_ptr<Game1> GAMES_ENTRY_POINT ()
{
    return std::make_unique<Game1>();
}