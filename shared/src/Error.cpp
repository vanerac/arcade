/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Error
*/

#include "Errors.hpp"

arcade::errors::Error::Error(const std::string &msg) : _msg("Error: " + msg)
{
}

arcade::errors::Error::~Error()
{
}

const char *arcade::errors::Error::what() const noexcept
{
    return _msg.c_str();
}