/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** main
*/

#include <iostream>
#include <algorithm>
#include "Arcade.hpp"
#include "Tools.hpp"
#include "Errors.hpp"

void D_print_vect(std::vector<std::string> &vect, const std::string &sectionName)
{
    std::cout << sectionName << std::endl;
    for (auto &t : vect) {
        std::cout << t << std::endl;
    }
    std::cout << "---" << std::endl;
}

static bool setArcade(arcade::Arcade &arcade, const std::string &firstGrLib)
{
    arcade.setGraphicalLibList("./lib");
    arcade.setGamesLibList("./games");

    // if (!arcade.getGalibsPath().size()) {
    //     std::cerr << "Error: No games were found in the './games' folder." << std::endl;
    //     return false;
    // }
    auto &grlibs = arcade.getGrlibsPath();
    if (!grlibs.size()) {
        std::cerr << "Error: No graphical lib were found in the './games' folder." << std::endl;
        return false;
    }
    for (unsigned int i = 0; i < grlibs.size(); ++i) {
        if (grlibs[0] == firstGrLib) {
            break;
        }
        std::rotate(grlibs.begin(), grlibs.begin() + 1, grlibs.end());
    }
    return true;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Error: You must give the first graphical lib to use." << std::endl;
        return 84;
    }
    arcade::Arcade arcade;

    std::string firstLib = av[1];
    firstLib = (Tools::Strings::startsWith(firstLib, "./") || firstLib[0] == '/' ? "" : "./") + firstLib;
    if (!setArcade(arcade, firstLib)) {
        return 84;
    }
    int status = 0;
    try
    {
        status = arcade.run();
    }
    catch(const Errors::Error& e)
    {
        std::cerr << e.what() << '\n';
        status = 84;
    }
    return status;
}









// int main()
// {
//     DLLoader loader{"./lib/arcade_sfml.so"};

//     if (!loader.didLoad()) {
//         std::cerr << "Could not open!!" << dlerror() << std::endl;
//         return 84;
//     }
//     std::unique_ptr<Displayer::IDisplay> (*getter)() = loader.getFunc<std::unique_ptr<Displayer::IDisplay> (*)()>("entry_point");
//     if (!getter) {
//         std::cerr << "Could not find getter!!" << std::endl;
//         return 84;
//     }
//     std::unique_ptr<Displayer::IDisplay> displayer = getter();
//     if (!displayer) {
//         std::cerr << "Could not create displayer!!" << std::endl;
//         return 84;
//     }
//     displayer->init();
//     displayer->stop();
//     return 0;
// }