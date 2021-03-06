/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibNCRS
*/

#include <array>
#include <algorithm>
#include <thread>
#include "LibNCRS.hpp"
#include "Errors.hpp"

LibNCRS::LibNCRS()
{
}

LibNCRS::~LibNCRS()
{
    if (isOpen()) {
        stop();
    }
}

int LibNCRS::availableOptions() const
{
    return NO_OPTIONS;
}

void LibNCRS::init(const std::string &winName, unsigned int framesLimit)
{
    (void)winName;
    _frameLimit = framesLimit;
    initscr();
    if (noecho() == ERR || curs_set(FALSE) == ERR || keypad(stdscr, TRUE) == ERR) {
        throw arcade::errors::Error("The ncurses lib could not been initialize properly.");
    }
    mousemask(ALL_MOUSE_EVENTS, NULL);
    start_color();
    refresh();
    timeout(0);
    restartClock();
}

void LibNCRS::stop()
{
    endwin();
}

bool LibNCRS::isOpen() const
{
    return isendwin();
}

void LibNCRS::clearWindow()
{
    erase();
}

void LibNCRS::display()
{
    refresh();
    double toWait = ((1.0f / _frameLimit) * 1000) - (getFrameDuration() * 1000);
    if (toWait > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(toWait)));
    }
    _lastFrameTime = getFrameDuration();
    _eventFetched = false;
    restartClock();
}

void LibNCRS::restartClock()
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

double LibNCRS::getDeltaTime() const
{
    return _lastFrameTime;
}

double LibNCRS::getFrameDuration() const
{
    return std::chrono::duration_cast
        <
        std::chrono::duration<double, std::ratio<1>>
        >
            (std::chrono::high_resolution_clock::now() - _timePoint).count();
}

arcade::data::Vector2u LibNCRS::getWindowSize() const
{
    unsigned int width = 0;
    unsigned int height = 0;
    getmaxyx(stdscr, height, width);
    return arcade::data::Vector2u{width, height};
}

std::vector<arcade::data::Event> LibNCRS::getEvents()
{
    if (_eventFetched) {
        return _events;
    }
    _eventFetched = true;
    _events.clear();
    int c = getch();
    if (c == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) == OK) {
            if (event.bstate == REPORT_MOUSE_POSITION) {
                _events.emplace_back(arcade::data::EventType::MOUSE_MOVED, event.x, event.y);
            } else {
                static const std::array<std::tuple<arcade::data::MouseBtn, uint64_t>, 4> ncrsBtsNb = {
                    std::tuple<arcade::data::MouseBtn, uint64_t>{arcade::data::MouseBtn::BTN_4, BUTTON4_RELEASED},
                    std::tuple<arcade::data::MouseBtn, uint64_t>{arcade::data::MouseBtn::BTN_3, BUTTON3_RELEASED},
                    std::tuple<arcade::data::MouseBtn, uint64_t>{arcade::data::MouseBtn::BTN_2, BUTTON2_RELEASED},
                    std::tuple<arcade::data::MouseBtn, uint64_t>{arcade::data::MouseBtn::BTN_1, BUTTON1_RELEASED},
                };
                auto it = std::find_if(ncrsBtsNb.begin(), ncrsBtsNb.end(),
                            [&event](auto &tupple) {
                                return event.bstate >= std::get<1>(tupple);
                            });
                if (it != ncrsBtsNb.end()) {
                    static const std::array<std::tuple<arcade::data::EventType, uint64_t>, 5> ncrsToArcadeMouseType = {
                        std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         NCURSES_DOUBLE_CLICKED},
                        std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         NCURSES_TRIPLE_CLICKED},
                        std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         NCURSES_BUTTON_CLICKED},
                        std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         NCURSES_BUTTON_PRESSED},
                        std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        NCURSES_BUTTON_RELEASED},
                    };
                    auto itT = std::find_if(ncrsToArcadeMouseType.begin(), ncrsToArcadeMouseType.end(),
                                    [&event](auto &tupple) {
                                        return event.bstate == std::get<1>(tupple);
                                    });
                    if (itT != ncrsToArcadeMouseType.end()) {
                        _events.emplace_back(std::get<0>(*itT), std::get<0>(*it), event.x, event.y);
                    }
                }
            }
        }
    } else if (c != ERR) {
        _events.emplace_back(arcade::data::EventType::KEY_PRESSED, static_cast<arcade::data::KeyCode>(c));
    }
    return _events;
}

void LibNCRS::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    if (!text) {
        return;
    }
    auto &t = reinterpret_cast<std::unique_ptr<TextNCRS> &>(text);
    auto pos = t->getPosition();
    auto org = t->getOrigin();
    int startX = pos.x - org.x;
    int startY = pos.y - org.y;
    auto win = getWindowSize();
    unsigned int size = t->getText().size();
    if (startY < 0 || startY >= static_cast<int>(win.y) || (startX + static_cast<int>(size) < 0) || (startX >= static_cast<int>(win.x))) {
        return;
    }
    const char *content = t->getString();
    attr_t att;
    NCURSES_PAIRS_T pair;
    short fg;
    short bg = COLOR_BLACK;
    for (unsigned int i = 0; i < size; ++i, ++content, ++startX) {
        if (startX < 0 || startX >= static_cast<int>(win.x) || *content == '\r') {
            continue;
        }
        move(startY, startX);
        attr_get(&att, &pair, NULL);
        pair_content(att, &fg, &bg);
        pair = getNcrsColorPair(t->getNcrsColor(), bg);
        addch(*content | COLOR_PAIR(pair));
    }
}

void LibNCRS::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    if (!sprite) {
        return;
    }
    auto &s = reinterpret_cast<std::unique_ptr<SpriteNCRS> &>(sprite);
    auto &img = s->getSprite();
    auto pos = s->getPosition();
    auto org = s->getOrigin();
    auto rect = s->getTextureRect();
    auto win = getWindowSize();
    int startX = pos.x - org.x;
    int startY = pos.y - org.y;
    int maxY = img.size();
    for (int y = rect.top, fetchingY; y < rect.height; ++y, ++startY) {
        if (startY < 0 || startY >= static_cast<int>(win.y)) {
            continue;
        }
        fetchingY = y < 0 ? 0 : (y >= maxY ? maxY - 1 : y);
        int maxX = img[fetchingY].size();
        for (int x = rect.left, fetchingX, counter = startX; x < rect.width; ++x, ++counter) {
            fetchingX = x < 0 ? 0 : (x >= maxX ? maxX - 1 : x);
            if (counter < 0 || counter >= static_cast<int>(win.x) || img[fetchingY][fetchingX] == '\r') {
                continue;
            }
            move(startY, counter);
            addch(img[fetchingY][fetchingX]);
        }
    }
}

std::unique_ptr<arcade::displayer::IText> LibNCRS::createText() const
{
    return std::make_unique<TextNCRS>();
}

std::unique_ptr<arcade::displayer::IText> LibNCRS::createText(const std::string &text) const
{
    return std::make_unique<TextNCRS>(text);
}

std::unique_ptr<arcade::displayer::ISprite> LibNCRS::createSprite() const
{
    return std::make_unique<SpriteNCRS>();
}

std::unique_ptr<arcade::displayer::ISprite> LibNCRS::createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale) const
{
    (void)spritePath;
    return std::make_unique<SpriteNCRS>(asciiSprite, scale);
}

double LibNCRS::scaleMoveX(double time) const
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().x / time) / (1.0f / getDeltaTime());
}

double LibNCRS::scaleMoveY(double time) const
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().y / time) / (1.0f / getDeltaTime());
}

NCURSES_PAIRS_T LibNCRS::getNcrsColorPair(short fg, short bg)
{
    static std::array<std::tuple<short, short, NCURSES_PAIRS_T>, 3> cache;
    static std::vector<std::tuple<short, short, NCURSES_PAIRS_T>> pairs;

    auto itCache = std::find_if(cache.begin(), cache.end(),
                    [fg, bg](auto &tupple) {
                        return std::get<0>(tupple) == fg && std::get<1>(tupple) == bg;
                    });
    if (itCache != cache.end()) {
        return std::get<2>(*itCache);
    }
    auto it = std::find_if(pairs.begin(), pairs.end(),
                [fg, bg](auto &tupple) {
                    return std::get<0>(tupple) == fg && std::get<1>(tupple) == bg;
                });
    if (it != pairs.end()) {
        std::rotate(cache.rbegin(), cache.rbegin() + 1, cache.rend());
        cache[0] = *it;
        return std::get<2>(*it);
    }
    short pair = pairs.size() + 2;
    init_pair(pair, fg, bg);
    pairs.emplace_back(fg, bg, pair);
    return pair;
}

std::pair<arcade::data::Color, NCURSES_PAIRS_T> LibNCRS::colorToNcrsColor(arcade::data::Color color)
{
    std::pair<arcade::data::Color, NCURSES_PAIRS_T> pair;
    float r = color.r;
    float g = color.g;
    float b = color.b;

    float total = r + g + b;

    if (r <= 90 && g <= 90 && b <= 90) {
        pair.first = arcade::data::Color::Black;
        pair.second = COLOR_BLACK;
    } else if (r / total >= 0.7) {
        pair.first = arcade::data::Color::Red;
        pair.second = COLOR_RED;
    } else if (g / total >= 0.7) {
        pair.first = arcade::data::Color::Green;
        pair.second = COLOR_GREEN;
    } else if (b / total >= 0.7) {
        pair.first = arcade::data::Color::Blue;
        pair.second = COLOR_BLUE;
    } else if (r >= 200 && g >= 200 && b <= 100) {
        pair.first = arcade::data::Color::Yellow;
        pair.second = COLOR_YELLOW;
    } else if (g >= 200 && b >= 200 && r <= 100) {
        pair.first = arcade::data::Color::Cyan;
        pair.second = COLOR_CYAN;
    } else if (r >= 200 && b >= 200 && g <= 100) {
        pair.first = arcade::data::Color::Magenta;
        pair.second = COLOR_MAGENTA;
    } else if (r >= 200 && g >= 200 && b >= 200) {
        pair.first = arcade::data::Color::White;
        pair.second = COLOR_WHITE;
    } else {
        pair.first = arcade::data::Color::Black;
        pair.second = COLOR_BLACK;
    }
    return pair;
}