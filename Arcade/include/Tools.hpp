/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Tools
*/

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <vector>
#include <string>

namespace Tools
{
    /*
     * Dirs
    */
    namespace Dirs
    {
        std::vector<std::string> lsDir(const std::string &dirPath, bool withPath = false);
        std::vector<std::string> lsDir(const std::string &dirPath, const std::string &ext, bool withPath = false);
    } // namespace Dirs


    /*
     * Strings
    */
    namespace Strings
    {
        bool endsWith(const std::string &stack, const std::string niddle);
        bool startsWith(const std::string &stack, const std::string niddle);
    } // namespace Strings
} // namespace Tools

#endif /* !TOOLS_HPP_ */
