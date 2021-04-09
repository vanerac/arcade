/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibError
*/

#include "ArcErrors.hpp"

arcade::errors::LibError::LibError(const std::string &msg) : _msg("Lib Error: " + msg)
{
}

arcade::errors::LibError::LibError(const std::string &msg, const std::string &cause) : _msg("Lib Error in '" + cause + "': " + msg)
{
}

arcade::errors::LibError::~LibError()
{
}

const char *arcade::errors::LibError::what() const noexcept
{
    return _msg.c_str();
}