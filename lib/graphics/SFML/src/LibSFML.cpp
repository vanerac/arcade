/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibSFML
*/

#include <iostream>
#include <unordered_map>
#include "LibSFML.hpp"
#include "Errors.hpp"

LibSFML::LibSFML()
{
    // stream.open("./log.txt");
    stream.open("./log.txt", std::ios_base::app);
}

LibSFML::~LibSFML()
{
    if (isOpen()) {
        stop();
    }
}

int LibSFML::availableOptions() const
{
    return SET_CHARACTER_SIZE | MOUSE_MOVE | SETTING_FONTS;
}

void LibSFML::init(const std::string &winName, unsigned int framesLimit)
{
    std::cout << "Init" << std::endl;
    _window.create(sf::VideoMode(1920, 1080), winName, sf::Style::Fullscreen);
    if (_window.isOpen() == false) {
        throw arcade::errors::Error("The SFML graphic lib could not been initialize properly.");
    }
    _window.setFramerateLimit(framesLimit);
    restartClock();
}

void LibSFML::stop()
{
    std::cout << "Stop" << std::endl;
    _window.close();
}

bool LibSFML::isOpen() const
{
    return _window.isOpen();
}

void LibSFML::clearWindow()
{
    _window.clear();
}

void LibSFML::display()
{
    _window.display();
    _lastFrameTime = getFrameDuration();
    _eventsFetched = false;
    restartClock();
}

void LibSFML::restartClock()
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

double LibSFML::getDeltaTime() const
{
    return _lastFrameTime;
}

double LibSFML::getFrameDuration() const
{
    return std::chrono::duration_cast
        <
        std::chrono::duration<double, std::ratio<1>>
        >
            (std::chrono::high_resolution_clock::now() - _timePoint).count();
}

arcade::data::Vector2u LibSFML::getWindowSize() const
{
    auto size = _window.getSize();
    return arcade::data::Vector2u{size.x, size.y};
}

std::vector<arcade::data::Event> LibSFML::getEvents()
{
    if (_eventsFetched) {
        return _events;
    }
    _eventsFetched = true;
    _events.clear();
    sf::Event event;
    static const std::unordered_map<sf::Keyboard::Key, char> sfToArcadeKey {
        {sf::Keyboard::LBracket,    '['},
        {sf::Keyboard::RBracket,    ']'},
        {sf::Keyboard::Semicolon,   ';'},
        {sf::Keyboard::Comma,       ','},
        {sf::Keyboard::Period,      '.'},
        {sf::Keyboard::Quote,       '\''},
        {sf::Keyboard::Slash,       '/'},
        {sf::Keyboard::Backslash,   '\\'},
        {sf::Keyboard::Tilde,       '~'},
        {sf::Keyboard::Equal,       '='},
        {sf::Keyboard::Hyphen,      '-'},
        {sf::Keyboard::Add,         '+'},
        {sf::Keyboard::Subtract,    '-'},
        {sf::Keyboard::Multiply,    '*'},
        {sf::Keyboard::Divide,      '/'},
    };
    static const std::unordered_map<sf::Keyboard::Key, arcade::data::KeyCode> sfToArcadeKeyCode {
        {sf::Keyboard::Enter,     arcade::data::KeyCode::ENTER},
        {sf::Keyboard::Backspace, arcade::data::KeyCode::BACKSPACE},
        {sf::Keyboard::Escape,    arcade::data::KeyCode::ESCAPE},
        {sf::Keyboard::Space,     arcade::data::KeyCode::SPACE},
        {sf::Keyboard::Down,      arcade::data::KeyCode::DOWN},
        {sf::Keyboard::Up,        arcade::data::KeyCode::UP},
        {sf::Keyboard::Left,      arcade::data::KeyCode::LEFT},
        {sf::Keyboard::Right,     arcade::data::KeyCode::RIGHT},
    };
    static const std::unordered_map<sf::Event::EventType, arcade::data::EventType> sfToArcadeMouseType {
        {sf::Event::EventType::MouseButtonPressed,  arcade::data::EventType::MOUSE_PRESSED},
        {sf::Event::EventType::MouseButtonReleased, arcade::data::EventType::MOUSE_RELEASED},
        {sf::Event::EventType::MouseMoved,          arcade::data::EventType::MOUSE_MOVED},
    };
    static const std::unordered_map<sf::Mouse::Button, arcade::data::MouseBtn> sfToArcadeMouseBtn {
        {sf::Mouse::Button::Left,   arcade::data::MouseBtn::BTN_1},
        {sf::Mouse::Button::Middle, arcade::data::MouseBtn::BTN_2},
        {sf::Mouse::Button::Right,  arcade::data::MouseBtn::BTN_3},
    };
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _events.emplace_back(arcade::data::EventType::WINDOW_CLOSED);
        } else if (event.type == sf::Event::EventType::KeyPressed) {
            char key = event.key.code;
            if (key <= sf::Keyboard::Z) {
                key += event.key.shift ? 'A' : 'a';
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, key);
            } else if ((key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9) || (key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9)) {
                key = '0' + (key - (key >= sf::Keyboard::Numpad0 ? sf::Keyboard::Numpad0 : sf::Keyboard::Num0));
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, key);
            } else if (sfToArcadeKeyCode.find(event.key.code) != sfToArcadeKeyCode.end()) {
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, sfToArcadeKeyCode.at(event.key.code));
            } else if (sfToArcadeKey.find(event.key.code) != sfToArcadeKey.end()) {
                _events.emplace_back(arcade::data::EventType::KEY_PRESSED, sfToArcadeKey.at(event.key.code));
            }
        } else if (sfToArcadeMouseType.find(event.type) != sfToArcadeMouseType.end()) {
            if (event.type == sf::Event::EventType::MouseMoved) {
                _events.emplace_back(arcade::data::EventType::MOUSE_MOVED, event.mouseMove.x, event.mouseMove.y);
            } else {
                _events.emplace_back(sfToArcadeMouseType.at(event.type), sfToArcadeMouseBtn.at(event.mouseButton.button), event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
    return _events;
}

void LibSFML::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    if (!text) {
        return;
    }
    _window.draw((reinterpret_cast<std::unique_ptr<TextSFML> &>(text))->getsfText());
}

void LibSFML::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    if (!sprite) {
        return;
    }
    _window.draw((reinterpret_cast<std::unique_ptr<SpriteSFML> &>(sprite))->getSprite());
}

std::unique_ptr<arcade::displayer::IText> LibSFML::createText() const
{
    return std::make_unique<TextSFML>();
}

std::unique_ptr<arcade::displayer::IText> LibSFML::createText(const std::string &text) const
{
    return std::make_unique<TextSFML>(text);
}

std::unique_ptr<arcade::displayer::ISprite> LibSFML::createSprite() const
{
    return std::make_unique<SpriteSFML>();
}

std::unique_ptr<arcade::displayer::ISprite> LibSFML::createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale) const
{
    (void)asciiSprite;
    return std::make_unique<SpriteSFML>(spritePath, scale);
}

double LibSFML::scaleMoveX(double time) const
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().x / time) / (1.0f / getDeltaTime());
}

double LibSFML::scaleMoveY(double time) const
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().y / time) / (1.0f / getDeltaTime());
}