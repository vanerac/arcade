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
#include "Games.hpp"

namespace arcade
{
    class Arcade {
        public:
            Arcade();
            ~Arcade();

            void setLibsList(const std::string &folder);
            void fetchHighScores();
            static void saveHighScores(const std::string &gameName, const std::string &playerName, unsigned int score);

            std::vector<std::string> &getGrlibsPath();
            std::vector<std::string> &getGalibsPath();

            static void printLibconfHelp(bool onCerr = false);

            int run();

            void setGrLib(int move);
            void setGaLib(int move);

            void handleEvents();

            void menuLoadDisplayer();
            void menuCreateBox(arcade::data::FloatRect rect, char corners = '#', char horizontal = '#', char vertical = '#', char fill = '\r');
            void menuCreateBox(arcade::data::FloatRect rect, char corners, char top, char bottom, char left, char right, char fill = '\r');
            void menuSetHighScoresText();
            void drawMenu();
            void menuHandleEvents();
            void goBackToMenu();

        protected:
        private:
            enum ArcadeStatus {
                QUITTING,
                MENU,
                IN_GAME,
            };
            void setValidLibs();

            std::vector<std::string> _grlibValid;
            std::vector<std::string> _galibValid;
            std::vector<std::string> _grlibsPath;
            std::vector<std::string> _galibsPath;
            int _gameLoaded = 0;
            DLLoader _grLoader;
            DLLoader _gaLoader;
            std::shared_ptr<arcade::displayer::IDisplay> _displayer;
            std::unique_ptr<arcade::games::IGame> _game;
            ArcadeStatus _status = ArcadeStatus::MENU;
            unsigned int _menuSelectedGame = 0;
            std::vector<std::vector<std::pair<std::string, std::size_t>>> _highScores;
            std::vector<std::unique_ptr<arcade::displayer::IText>> _menuGamesListText;
            std::vector<std::unique_ptr<arcade::displayer::IText>> _menuGrListText;
            std::vector<std::unique_ptr<arcade::displayer::ISprite>> _menuBoxes;
            std::vector<std::unique_ptr<arcade::displayer::IText>> _menuInstructions;
            std::unique_ptr<arcade::displayer::IText> _menuHighScoreText;
            std::vector<std::unique_ptr<arcade::displayer::IText>> _menuHighScoresText;
            std::unique_ptr<arcade::displayer::IText> _menuNewGameText;
            std::unique_ptr<arcade::displayer::IText> _menuAskPlayerNameText;
            std::unique_ptr<arcade::displayer::IText> _menuPlayerNameText;
            std::string _playerName{"player"};
            unsigned int _score = 250;
            std::unique_ptr<arcade::displayer::ISprite> _menuGameEndedBox;
            std::unique_ptr<arcade::displayer::IText> _menuGameEndedText;
            std::unique_ptr<arcade::displayer::IText> _menuYourScoreText;
            std::unique_ptr<arcade::displayer::IText> _menuScoreText;
            bool _scoreIsToDisplay = false;

            std::unique_ptr<arcade::displayer::IText> _menuQuitText;
            std::unique_ptr<arcade::displayer::ISprite> _pacman;
    };
} // namespace arcade


#endif /* !ARCADE_HPP_ */
