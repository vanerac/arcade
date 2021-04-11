/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** entry_point
*/

#include <memory>
#include "Nibbler.hpp"

extern "C" std::unique_ptr<Nibbler> GAMES_ENTRY_POINT ()
{
    return std::make_unique<Nibbler>();
}