/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** entry_point
*/

#include <memory>
#include "LibSDL2.hpp"

extern "C" std::unique_ptr<LibSDL2> DISPLAYER_ENTRY_POINT ()
{
    return std::make_unique<LibSDL2>();
}