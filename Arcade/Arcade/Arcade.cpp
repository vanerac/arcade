/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Arcade
*/

#include <algorithm>
#include <regex>
#include "Arcade.hpp"
#include "Tools.hpp"
#include "Errors.hpp"

arcade::Arcade::Arcade()
{
}

arcade::Arcade::~Arcade()
{
}

void arcade::Arcade::setValidLibs()
{
    _validSet = true;
    std::ifstream stream{"lib.conf"};
    if (!stream) {
        std::string error{"Could not read the file 'lib.conf'.\n"};
        error += "\nPlease create a 'lib.conf' file, and add:";
        error += "\n  [graphics:] section with all the valid names of graphical libraries.";
        error += "\n  [games:] section with all the valid names of games libraries.";
        error += "\n\nexemple:";
        error += "\n[";
        error += "\ngaphics:";
        error += "\n  arcade_sfml.so";
        error += "\ngames:";
        error += "\n  arcade_pacman.so";
        error += "\n]";
        throw Errors::Error(error);
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
                throw Errors::Error("Unknown section '" + setcion + "' in the 'lib.conf' file.");
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
                throw Errors::Error("Unexpected error while parsing 'lib.conf' file.");
            }
        } else {
            if (status == 0) {
                throw Errors::Error("No section were set before: '" + line + "'.");
            } else {
                throw Errors::Error("Invalid line '" + line + "' in the 'lib.conf' file.");
            }
        }
    }
    if (save != 5) {
        std::string which;
        which += (save & 1) ? "" : "'graphics'";
        which += (save & 4) ? "" : (save & 1 ? "" : " and ");
        which += (save & 4) ? "" : "'games'";
        throw Errors::Error("No valid " + which + " were set in 'lib.conf' file.");
    }
}

void arcade::Arcade::setLibsList(const std::string &folder)
{
    if (!_validSet) {
        setValidLibs();
    }
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
}

void arcade::Arcade::setGraphicalLibList(const std::string &grlibsFolder)
{
    if (!_validSet) {
        setValidLibs();
    }
    _grlibsPath = Tools::Dirs::lsDir(grlibsFolder, ".so", true);
}

void arcade::Arcade::setGamesLibList(const std::string &galibsFolder)
{
    if (!_validSet) {
        setValidLibs();
    }
    _galibsPath = Tools::Dirs::lsDir(galibsFolder, ".so", true);
}

std::vector<std::string> &arcade::Arcade::getGrlibsPath()
{
    return _grlibsPath;
}

std::vector<std::string> &arcade::Arcade::getGalibsPath()
{
    return _galibsPath;
}

int arcade::Arcade::run()
{
    if (!_grlibsPath.size()) {//} || !_galibsPath.size()) {
        throw Errors::Error("Not enought libs.");
    }
    setGrLib(0);
    // setGaLib();
    menuInitElems();
    _displayer->restartClock();
    while (_status != ArcadeStatus::QUITTING) {
        handleEvents();
        if (_status == ArcadeStatus::MENU) {
            // std::cerr << "Yep" << std::endl;
            drawMenu();
            // std::cerr << "Yep Again" << std::endl;
        } else if (_status != ArcadeStatus::QUITTING) {
            // draw game
        }
        _displayer->display();
    }
    _displayer->stop();
    return 0;
}
#include <chrono>
#include <thread>
void arcade::Arcade::handleEvents()
{
    auto events = _displayer->getEvents();

    for (auto &event : events) {
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            if (event.keyCode == arcade::data::KeyCode::ESCAPE) {
                _status = ArcadeStatus::QUITTING;
                // std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(350)));
                // _pacman->rotate(25);
            } else if (event.key == '2') {
                setGrLib(1);
            } else if (event.key == '1') {
                setGrLib(-1);
            }
        }
    }
}

void arcade::Arcade::setGrLib(int move)
{
    if (!_grlibsPath.size()) {
        throw Errors::Error("No libs set.");
    }
    if (_grlibsPath.size() > 1) {
        if (move >= 0) {
            std::rotate(_grlibsPath.begin(), _grlibsPath.begin() + move, _grlibsPath.end());
        } else {
            std::rotate(_grlibsPath.rbegin(), _grlibsPath.rbegin() - move, _grlibsPath.rend());
        }
    }
    const std::string path = _grlibsPath[0];
    if (_displayer) {
        _displayer->stop();
    }
    if (!_grLoader.load(path)) {
        throw Errors::Error(_grLoader.getErrorMsg());
    }
    #define str(s)  #s
    #define xstr(s) str(s)
    auto entry = _grLoader.getFunc<std::unique_ptr<arcade::displayer::IDisplay> (*)()>(xstr(DISPLAYER_ENTRY_POINT));
    if (!entry) {
        throw Errors::Error("No entry point were found for the lib '" + path + "' (searching: '" + xstr(DISPLAYER_ENTRY_POINT) + "'.");
    }
    #undef  str
    #undef  xstr
    _displayer = entry();
    if (!_displayer) {
        throw Errors::Error("The entry point returned a null pointer ('" + path + "').");
    }
    _displayer->init("Arcade", 60);
    menuLoadDisplayer();
}

void arcade::Arcade::setGaLib()
{
    if (!_galibsPath.size()) {
        throw Errors::Error("No libs set.");
    }
    const std::string &path = _galibsPath[0];
    if (_galibsPath.size() > 1) {
        std::rotate(_galibsPath.begin(), _galibsPath.begin() + 1, _galibsPath.end());
    }
    if (!_gaLoader.load(path)) {
        throw Errors::Error(_gaLoader.getErrorMsg());
    }
    // #define str(s)  #s
    // #define xstr(s) str(s)
    // auto entry = _gaLoader.getFunc<std::unique_ptr<Displayer::IDisplay> (*)()>(xstr(DISPLAYER_ENTRY_POINT));
    // if (!entry) {
    //     throw Errors::Error("No entry point were found for the lib '" + path + "' (searching: '" + xstr(DISPLAYER_ENTRY_POINT) + "'.");
    // }
    // #undef  str
    // #undef  xstr
    // std::unique_ptr<Displayer::IDisplay> displayer = entry();
}