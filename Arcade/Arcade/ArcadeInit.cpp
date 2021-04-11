/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** ArcadeInit
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include "Arcade.hpp"
#include "Tools.hpp"
#include "ArcErrors.hpp"

void arcade::Arcade::printLibconfHelp(bool onCerr)
{
    auto &out = onCerr ? std::cerr : std::cout;
    out << '\n' << "[lib.conf]: is the file to set all the valid libs to be used:" << '\n';
    out << "  [graphics:] section with all the valid names of graphical libraries." << '\n';
    out << "  [games:] section with all the valid names of games libraries." << '\n';
    out << "exemple:" << '\n';
    out << "[" << '\n';
    out << "gaphics:" << '\n';
    out << "  arcade_sfml.so" << '\n';
    out << "games:" << '\n';
    out << "  arcade_pacman.so" << '\n';
    out << "]" << '\n';
}

void arcade::Arcade::setValidLibs()
{
    std::ifstream stream{"./lib.conf"};
    if (!stream) {
        throw arcade::errors::LibError("Could not read the file 'lib.conf'.");
    }
    std::regex findSection{"(?:\n|^)([\\w]+):[ \t]*(?:#|\n|$)"};
    std::regex nullLineFinder("(?:\n|^)[ \t]*(?:#|\n|$)");
    std::regex findName{"(?:\n|^)[ \t]*([\\w.]+)[ \t]*(?:#|\n|$)"};
    std::smatch match;
    int save = 0;
    int status = 0;

    for (std::string line; std::getline(stream, line);) {
        if (std::regex_search(line, match, findSection)) {
            auto setcion = match[1].str();
            int tmpstatus = setcion == "graphics" ? 1 : (setcion == "games" ? 4 : -1);
            if (tmpstatus == -1) {
                throw arcade::errors::LibError("Unknown section '" + setcion + "'.", "lib.conf");
            }
            save |= tmpstatus;
            status = tmpstatus;
        } else if (std::regex_search(line, match, nullLineFinder)) {
            continue;
        } else if (status && std::regex_search(line, match, findName)) {
            if (status & 1) {
                _grlibValid.emplace_back(match[1].str());
            } else if (status & 4) {
                _galibValid.emplace_back(match[1].str());
            } else {
                throw arcade::errors::LibError("Unexpected error while parsing.", "lib.conf");
            }
        } else {
            if (status == 0) {
                throw arcade::errors::LibError("No section were set before: '" + line + "'.", "lib.conf");
            } else {
                throw arcade::errors::LibError("Invalid line '" + line + "'.", "lib.conf");
            }
        }
    }
    if (save != 5 || _galibValid.size() == 0 || _grlibValid.size() == 0) {
        std::string which;
        which += (save & 1 && _grlibValid.size()) ? "" : "'graphics'";
        which += (save & 4 && _galibValid.size()) ? "" : (save & 1 && _grlibValid.size() ? "" : " and ");
        which += (save & 4 && _galibValid.size()) ? "" : "'games'";
        throw arcade::errors::LibError("No valid " + which + " were set.", "lib.conf");
    }
}

void arcade::Arcade::setLibsList(const std::string &folder)
{
    setValidLibs();
    auto allLibs = Tools::Dirs::lsDir(folder, ".so", true);
    for (auto lib : allLibs) {
        auto path = lib;
        std::size_t s = lib.find_last_of('/');
        if (s != std::string::npos && ++s < lib.size()) {
            lib = lib.substr(s);
        }
        auto it = std::find(_grlibValid.begin(), _grlibValid.end(), lib);
        if (it != _grlibValid.end()) {
            _grlibsPath.emplace_back(path);
        } else {
            it = std::find(_galibValid.begin(), _galibValid.end(), lib);
            if (it != _galibValid.end()) {
                _galibsPath.emplace_back(path);
            }
        }
    }
    fetchHighScores();
}

void arcade::Arcade::saveHighScores(const std::string &gameName, const std::string &playerName, unsigned int score)
{
    std::ofstream stream;
    stream.open("./.highscores.conf", std::ios_base::app);
    if (!stream) {
        return;
    }
    auto game = gameName;
    std::size_t it = game.find_last_of('/');
    if (it != std::string::npos && ++it < game.size()) {
        game = game.substr(it);
    }
    stream << '\n' << game << ':' << '\n' << "    " << playerName << ": " << score;
    stream.close();
}

void arcade::Arcade::fetchHighScores()
{
    if (!_galibsPath.size()) {
        return;
    }
    std::ifstream stream{"./.highscores.conf"};
    if (!stream) {
        return;
    }
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::size_t>>>> highScores;
    std::regex findSection{"(?:\n|^)([\\w\\d.]+):[ \t]*(?:#|\n|$)"};
    std::regex nullLineFinder("(?:\n|^)[ \t]*(?:#|\n|$)");
    std::regex findScore{"(?:\n|^)[ \t]*([\\w\\d\\-]{1,8})[ \t]*:[ \t]*(\\d+)(?:#|\n|$)"};
    std::smatch match;
    int status = -1;

    for (std::string line; std::getline(stream, line);) {
        if (std::regex_search(line, match, findSection)) {
            auto setcion = match[1].str();
            auto it = std::find_if(highScores.begin(), highScores.end(),
                                    [&setcion](auto &pair) {
                                        return pair.first == setcion;
                                    });
            if (it != highScores.end()) {
                status = it - highScores.begin();
            } else {
                highScores.push_back({setcion, std::vector<std::pair<std::string, std::size_t>>{0}});
                status = highScores.size() - 1;
            }
        } else if (std::regex_search(line, match, nullLineFinder)) {
            continue;
        } else if (status != -1 && std::regex_search(line, match, findScore)) {
            highScores[status].second.emplace_back(match[1].str(), std::stoul(match[2].str()));
        } else {
            continue;
        }
    }
    _highScores.clear();
    auto games = _galibsPath;
    _highScores.resize(games.size());
    for (auto &game : games) {
        std::size_t it = game.find_last_of('/');
        if (it != std::string::npos && ++it < game.size()) {
            game = game.substr(it);
        }
    }
    for (auto &gamePair : highScores) {
        auto it = std::find(games.begin(), games.end(), gamePair.first);
        if (it != games.end()) {
            std::sort(gamePair.second.begin(), gamePair.second.end(),
                        [](auto &pa, auto &pb) {
                            return pa.second > pb.second;
                        });
            gamePair.second.erase(std::unique(gamePair.second.begin(), gamePair.second.end()), gamePair.second.end());
            _highScores[it - games.begin()] = gamePair.second;
        }
    }
}

void arcade::Arcade::setGrLib(int move)
{
    if (!_grlibsPath.size()) {
        throw arcade::errors::LibError("No libs set.");
    }
    if (_grlibsPath.size() > 1 && move) {
        if (move > 0) {
            std::rotate(_grlibsPath.begin(), _grlibsPath.begin() + move, _grlibsPath.end());
        } else {
            std::rotate(_grlibsPath.rbegin(), _grlibsPath.rbegin() - move, _grlibsPath.rend());
        }
    }
    const std::string path = _grlibsPath[0];
    if (_displayer) {
        _displayer->stop();
    }
    if (!_grLoader.load(path, RTLD_NOW | RTLD_NODELETE)) {
        throw arcade::errors::Error(_grLoader.getErrorMsg());
    }
    #define str(s)  #s
    #define xstr(s) str(s)
    auto entry = _grLoader.getFunc<std::unique_ptr<arcade::displayer::IDisplay> (*)()>(xstr(DISPLAYER_ENTRY_POINT));
    if (!entry) {
        throw arcade::errors::Error("No entry point were found for the lib '" + path + "' (searching: '" + xstr(DISPLAYER_ENTRY_POINT) + "'.");
    }
    #undef  str
    #undef  xstr
    _displayer = entry();
    if (!_displayer) {
        throw arcade::errors::Error("The entry point returned a null pointer ('" + path + "').");
    }
    _displayer->init("Arcade", 60);
    menuLoadDisplayer();
    if (_status == ArcadeStatus::IN_GAME && _game) {
        _game->init(_displayer);
    }
}

void arcade::Arcade::setGaLib(int move)
{
    if (!_galibsPath.size()) {
        throw arcade::errors::LibError("No libs set.");
    }
    if (!_displayer) {
        throw arcade::errors::LibError("No graphic libs set.");
    }
    _scoreIsToDisplay = false;
    _gameLoaded += move;
    _gameLoaded %= _galibsPath.size();
    _gameLoaded = _gameLoaded < 0 ? _galibsPath.size() + _gameLoaded : _gameLoaded;
    const std::string path = _galibsPath[_gameLoaded];
    if (_game && _status == ArcadeStatus::IN_GAME) {
        _game->stop();
    }
    if (!_gaLoader.load(path, RTLD_NOW | RTLD_NODELETE)) {
        throw arcade::errors::Error(_gaLoader.getErrorMsg());
    }
    #define str(s)  #s
    #define xstr(s) str(s)
    auto entry = _gaLoader.getFunc<std::unique_ptr<arcade::games::IGame> (*)()>(xstr(GAMES_ENTRY_POINT));
    if (!entry) {
        throw arcade::errors::Error("No entry point were found for the lib '" + path + "' (searching: '" + xstr(GAMES_ENTRY_POINT) + "'.");
    }
    #undef  str
    #undef  xstr
    _game = entry();
    if (!_game) {
        throw arcade::errors::Error("The entry point returned a null pointer ('" + path + "').");
    }
    _game->init(_displayer);
}