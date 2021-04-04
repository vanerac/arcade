/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibError
*/

#include "Errors.hpp"

Errors::LibError::LibError(const std::string &msg) : _msg("Lib Error: " + msg)
{
}

Errors::LibError::LibError(const std::string &msg, const std::string &cause) : _msg("Lib Error in '" + cause + "': " + msg)
{
}

Errors::LibError::~LibError()
{
}

const char *Errors::LibError::what() const noexcept
{
    return _msg.c_str();
}