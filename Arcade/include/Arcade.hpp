/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <iostream>

#include <string>
#include <vector>
#include <memory>
#include "DLLoader.hpp"
#include "Displayer.hpp"

namespace arcade
{
    // class Menu {
    //     public:
    //         Menu();
    //         ~Menu();

    //         void loadDisplayer(std::shared_ptr<arcade::displayer::IDisplay> displayer);
    //         void draw();

    //     protected:
    //     private:
    //         std::shared_ptr<arcade::displayer::IDisplay> _displayer;
    //         std::vector<std::unique_ptr<arcade::displayer::IText>> _gamesList;
    //         std::unique_ptr<arcade::displayer::IText> _quitText;
    // };

    class Arcade {
        public:
            Arcade();
            ~Arcade();

            void setGraphicalLibList(const std::string &grlibsFolder);
            void setGamesLibList(const std::string &galibsFolder);

            std::vector<std::string> &getGrlibsPath();
            std::vector<std::string> &getGalibsPath();

            int run();

            void setGrLib(int move);
            void setGaLib();

            void handleEvents();

            void menuLoadDisplayer();
            void drawMenu();

        protected:
        private:
            enum ArcadeStatus {
                QUITTING,
                MENU,
            };

            std::vector<std::string> _grlibsPath;
            std::vector<std::string> _galibsPath;
            DLLoader _grLoader;
            DLLoader _gaLoader;
            ArcadeStatus _status = ArcadeStatus::MENU;
            std::shared_ptr<arcade::displayer::IDisplay> _displayer;
            std::vector<std::unique_ptr<arcade::displayer::IText>> _menuGamesListText;
            std::unique_ptr<arcade::displayer::IText> _menuQuitText;
            std::unique_ptr<arcade::displayer::ISprite> _pacman;
    };
} // namespace arcade


#endif /* !ARCADE_HPP_ */
