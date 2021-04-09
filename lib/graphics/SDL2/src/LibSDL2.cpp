/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibSDL2
*/

#include <iostream>
#include <unordered_map>
#include <thread>
#include "LibSDL2.hpp"
#include "Errors.hpp"

RendererPtr LibSDL2::renderer = nullptr;

LibSDL2::LibSDL2()
{
    // stream.open("./log.txt");
    stream.open("./log.txt", std::ios_base::app);
}

LibSDL2::~LibSDL2()
{
    std::cout << "SDL2 lib is being destroyed" << std::endl;
    if (isOpen()) {
        stop();
    }
}

int LibSDL2::availableOptions() const
{
    return SET_CHARACTER_SIZE | MOUSE_MOVE | SETTING_FONTS;
}

void LibSDL2::init(const std::string &winName, unsigned int framesLimit)
{
    std::cout << "Init" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0
    || !(_window = make_window(SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP)))
    || !(LibSDL2::renderer = make_renderer(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED)))) {
        throw arcade::errors::Error(std::string{"The SDL2 graphic lib could not been initialize properly: "} + SDL_GetError());
    }
    _frameLimit = framesLimit;
    _windowIsOpen = true;
    restartClock();
}

void LibSDL2::stop()
{
    std::cout << "Stop" << std::endl;
    _window.reset();
    LibSDL2::renderer.reset();
    SDL_Quit();
    TTF_Quit();
    _windowIsOpen = false;
}

bool LibSDL2::isOpen()
{
    return _windowIsOpen;
}

void LibSDL2::clearWindow()
{
    if (SDL_RenderClear(LibSDL2::renderer.get()) < 0) {
        throw arcade::errors::Error(std::string{"Could not clear the window: "} + SDL_GetError());
    }
}

void LibSDL2::display()
{
    SDL_RenderPresent(LibSDL2::renderer.get());
    double toWait = ((1.0f / _frameLimit) * 1000) - (getFrameDuration() * 1000);
    if (toWait > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(toWait)));
    }
    _lastFrameTime = getFrameDuration();
    _eventsFetched = false;
    restartClock();
}

void LibSDL2::restartClock()
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

double LibSDL2::getDeltaTime()
{
    return _lastFrameTime;
}

double LibSDL2::getFrameDuration() const
{
    return std::chrono::duration_cast
        <
        std::chrono::duration<double, std::ratio<1>>
        >
            (std::chrono::high_resolution_clock::now() - _timePoint).count();
}

arcade::data::Vector2u LibSDL2::getWindowSize()
{
    int x = 0;
    int y = 0;
    SDL_GetWindowSize(&*_window, &x, &y);
    return arcade::data::Vector2i{x, y};
}

std::vector<arcade::data::Event> LibSDL2::getEvents()
{
    if (_eventsFetched) {
        return _events;
    }
    _eventsFetched = true;
    _events.clear();
    static const std::unordered_map<int, char> sdl2ToArcadeKey {
        {SDLK_KP_DIVIDE,    '/'},
        {SDLK_KP_MULTIPLY,  '*'},
        {SDLK_KP_MINUS,     '-'},
        {SDLK_KP_PLUS,      '+'},
        {SDLK_KP_EQUALS,    '='},
        {SDLK_POWER,        '*'},
        {SDLK_KP_0,         '0'},
        {SDLK_KP_1,         '1'},
        {SDLK_KP_2,         '2'},
        {SDLK_KP_3,         '3'},
        {SDLK_KP_4,         '4'},
        {SDLK_KP_5,         '5'},
        {SDLK_KP_6,         '6'},
        {SDLK_KP_7,         '7'},
        {SDLK_KP_8,         '8'},
        {SDLK_KP_9,         '9'},
    };
    static const std::unordered_map<int, arcade::data::KeyCode> sdl2ToArcadeKeyCode {
        {SDLK_RETURN,    arcade::data::KeyCode::ENTER},
        {SDLK_RETURN2,   arcade::data::KeyCode::ENTER},
        {SDLK_KP_ENTER,  arcade::data::KeyCode::ENTER},
        {SDLK_BACKSPACE, arcade::data::KeyCode::BACKSPACE},
        {SDLK_ESCAPE,    arcade::data::KeyCode::ESCAPE},
        {SDLK_SPACE,     arcade::data::KeyCode::SPACE},
        {SDLK_DOWN,      arcade::data::KeyCode::DOWN},
        {SDLK_UP,        arcade::data::KeyCode::UP},
        {SDLK_LEFT,      arcade::data::KeyCode::LEFT},
        {SDLK_RIGHT,     arcade::data::KeyCode::RIGHT},
    };
    static const std::unordered_map<int, arcade::data::MouseBtn> sdl2ToArcadeMouseBtn {
        {SDL_BUTTON_LEFT,   arcade::data::MouseBtn::BTN_1},
        {SDL_BUTTON_MIDDLE, arcade::data::MouseBtn::BTN_2},
        {SDL_BUTTON_RIGHT,  arcade::data::MouseBtn::BTN_3},
    };
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            _events.emplace_back(arcade::data::EventType::WINDOW_CLOSED);
        } else if (_event.type == SDL_KEYDOWN) {
            if (sdl2ToArcadeKeyCode.find(_event.key.keysym.sym) != sdl2ToArcadeKeyCode.end()) {
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, sdl2ToArcadeKeyCode.at(_event.key.keysym.sym));
            } else if (sdl2ToArcadeKey.find(_event.key.keysym.sym) != sdl2ToArcadeKey.end()) {
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, sdl2ToArcadeKey.at(_event.key.keysym.sym));
            } else if (_event.key.keysym.sym <= '~') {
                char c = _event.key.keysym.sym;
                if (_event.key.keysym.mod & KMOD_SHIFT) {
                    if ('a' <= c && c <= 'z') {
                        c -= 'a' - 'A';
                    } else {
                        c = c == ':' ? '/' : (c == ';' ? '.' : (c == ',' ? '?' : c));
                    }
                }
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, c);
            }
        } else if ((_event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP)
        && sdl2ToArcadeMouseBtn.find(_event.button.button) != sdl2ToArcadeMouseBtn.end()) {
            _events.emplace_back(_event.type == SDL_MOUSEBUTTONDOWN ? arcade::data::EventType::MOUSE_PRESSED : arcade::data::EventType::MOUSE_RELEASED, sdl2ToArcadeMouseBtn.at(_event.button.button), _event.button.x, _event.button.y);
        } else if (_event.type == SDL_MOUSEMOTION) {
            _events.emplace_back(arcade::data::EventType::MOUSE_MOVED, _event.motion.x, _event.motion.y);
        }
    }
    return _events;
}

void LibSDL2::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    if (!text) {
        return;
    }
    (reinterpret_cast<std::unique_ptr<TextSDL2> &>(text))->draw();
}

void LibSDL2::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    if (!sprite) {
        return;
    }
    reinterpret_cast<std::unique_ptr<SpriteSDL2> &>(sprite)->draw();
}

std::unique_ptr<arcade::displayer::IText> LibSDL2::createText()
{
    return std::make_unique<TextSDL2>();
}

std::unique_ptr<arcade::displayer::IText> LibSDL2::createText(const std::string &text)
{
    return std::make_unique<TextSDL2>(text);
}

std::unique_ptr<arcade::displayer::ISprite> LibSDL2::createSprite()
{
    return std::make_unique<SpriteSDL2>();
}

std::unique_ptr<arcade::displayer::ISprite> LibSDL2::createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
{
    (void)asciiSprite;
    return std::make_unique<SpriteSDL2>(spritePath, scale);
}

double LibSDL2::scaleMoveX(double time)
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().x / time) / (1.0f / getDeltaTime());
}

double LibSDL2::scaleMoveY(double time)
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().y / time) / (1.0f / getDeltaTime());
}