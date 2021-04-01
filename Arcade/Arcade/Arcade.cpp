/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** Arcade
*/

#include <algorithm>
#include "Arcade.hpp"
#include "Tools.hpp"
#include "Errors.hpp"

arcade::Arcade::Arcade()
{
}

arcade::Arcade::~Arcade()
{
}

void arcade::Arcade::setGraphicalLibList(const std::string &grlibsFolder)
{
    _grlibsPath = Tools::Dirs::lsDir(grlibsFolder, ".so", true);
}

void arcade::Arcade::setGamesLibList(const std::string &galibsFolder)
{
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
    _displayer->init();
    menuLoadDisplayer();
    // int status = -1;
    _displayer->restartClock();
    while (_status != ArcadeStatus::QUITTING) {
        // Check lib chagement
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

void arcade::Arcade::handleEvents()
{
    auto events = _displayer->getEvents();

    for (auto &event : events) {
        // _displayer->log() << "[" << event.type << ", " << event.keyCode << ", " << event.x << ", " << event.y << "]" << std::endl;
        if (event.type == arcade::data::EventType::KEY_PRESSED && event.keyCode == arcade::data::KeyCode::ESCAPE) {
            _status = ArcadeStatus::QUITTING;
        } else if (event.key == '2') {
            setGrLib(1);
        }
    }
}

void arcade::Arcade::setGrLib(int move)
{
    (void)move;
    if (!_grlibsPath.size()) {
        throw Errors::Error("No libs set.");
    }
    const std::string path = _grlibsPath[0];
    if (_grlibsPath.size() > 1) {
        std::rotate(_grlibsPath.begin(), _grlibsPath.begin() + 1, _grlibsPath.end());
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