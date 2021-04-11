/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** main
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include "Arcade.hpp"
#include "Tools.hpp"
#include "ArcErrors.hpp"

static void print_help()
{
    std::cout << '\n' << "Usage: ./arcade <first-graphic-lib-to-use>" << '\n';
    std::cout << "  [./lib/]: the folder with all the necessary libs." << '\n';
    std::cout << "  [./ressources/]: the folder with all the sprites and other ressources." << '\n';
    arcade::Arcade::printLibconfHelp();
}

bool check_env(char **env)
{
    unsigned short found = 0;
    for (; *env; ++env) {
        if (!strcmp(*env, "DISPLAY=:0.0") || !strcmp(*env, "XDG_RUNTIME_DIR=/run/user/1000")) {
            ++found;
        }
    }
    return found == 2;
}

static void setArcade(arcade::Arcade &arcade, const std::string &firstGrLib)
{
    arcade.setLibsList("./lib");

    if (!arcade.getGalibsPath().size()) {
        throw arcade::errors::LibError("No games were found in the './lib' folder.");
    }
    auto &grlibs = arcade.getGrlibsPath();
    if (!grlibs.size()) {
        throw arcade::errors::LibError("No graphical lib were found in the './lib' folder.");
    }
    unsigned int i = 0;
    for (; i < grlibs.size(); ++i) {
        if (grlibs[0] == firstGrLib) {
            break;
        }
        std::rotate(grlibs.begin(), grlibs.begin() + 1, grlibs.end());
    }
    if (i == grlibs.size()) {
        throw arcade::errors::LibError("The lib '" + firstGrLib + "' could not been loaded.");
    }
}

int main(int ac, char **av, char **env)
{
    if (ac != 2) {
        std::cerr << "Error: You must give the first graphical lib to use." << std::endl;
        return 84;
    }
    if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help")) {
        print_help();
        return 0;
    } else if (!check_env(env)) {
        std::cerr << "Make sure the DISPLAY and XDG_RUNTIME_DIR environment variable is set correctly." << '\n';
        return 84;
    }
    std::srand(time(0));
    arcade::Arcade arcade;

    std::string firstLib = av[1];
    firstLib = (Tools::Strings::startsWith(firstLib, "./") || firstLib[0] == '/' ? "" : "./") + firstLib;
    int status = 0;
    try
    {
        setArcade(arcade, firstLib);
        status = arcade.run();
    }
    catch(const arcade::errors::Error& e)
    {
        std::cerr << e.what() << '\n';
        status = 84;
    }
    catch(const arcade::errors::LibError& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << '\n' << "You should maybe check the 'lib.conf' file." << '\n';
        std::cerr << "Get more info with the -h flag." << '\n';
        status = 84;
    }
    catch(...) {
        std::cerr << "Ooooh nooooooo" << '\n';
    }
    return status;
}