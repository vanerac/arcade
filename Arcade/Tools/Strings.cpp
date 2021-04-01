/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Strings
*/

#include "Tools.hpp"

bool Tools::Strings::endsWith(const std::string &stack, const std::string niddle)
{
    if (stack.length() >= niddle.length()) {
        return stack.compare(stack.length() - niddle.length(), niddle.length(), niddle) == 0;
    }
    return false;
}

bool Tools::Strings::startsWith(const std::string &stack, const std::string niddle)
{
    if (stack.length() >= niddle.length()) {
        return stack.compare(0, niddle.length(), niddle) == 0;
    }
    return false;
}