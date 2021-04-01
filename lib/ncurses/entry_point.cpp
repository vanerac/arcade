/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** entry_point
*/

#include <memory>
#include "LibNCRS.hpp"

extern "C" std::unique_ptr<LibNCRS> DISPLAYER_ENTRY_POINT ()
{
    return std::make_unique<LibNCRS>();
}