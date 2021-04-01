/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** LibNCRS
*/

#include <iostream>
#include <array>
#include <algorithm>
#include "LibNCRS.hpp"

static const std::array<std::tuple<arcade::data::EventType, uint64_t>, 20> ncrsToArcadeMouseType = {
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         BUTTON1_RELEASED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON1_PRESSED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON1_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_DOUBLE_CLICKED,  BUTTON1_DOUBLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_TRIPLE_CLICKED,  BUTTON1_TRIPLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         BUTTON2_RELEASED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON2_PRESSED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON2_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_DOUBLE_CLICKED,  BUTTON2_DOUBLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_TRIPLE_CLICKED,  BUTTON2_TRIPLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         BUTTON3_RELEASED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON3_PRESSED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON3_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_DOUBLE_CLICKED,  BUTTON3_DOUBLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_TRIPLE_CLICKED,  BUTTON3_TRIPLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_PRESSED,         BUTTON4_RELEASED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON4_PRESSED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_RELEASED,        BUTTON4_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_DOUBLE_CLICKED,  BUTTON4_DOUBLE_CLICKED},
    std::tuple<arcade::data::EventType, uint64_t>{arcade::data::EventType::MOUSE_TRIPLE_CLICKED,  BUTTON4_TRIPLE_CLICKED},
};

LibNCRS::LibNCRS() : stream("./log.txt")
{
}

LibNCRS::~LibNCRS()
{
}

std::ofstream &LibNCRS::log()
{
    return stream;
}

int LibNCRS::availableOptions() const
{
    return NO_OPTIONS;
}

void LibNCRS::init()
{
    std::cout << "Init" << std::endl;
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    timeout((1.0f / 60) * 1000);
    timeout(500);
    start_color();
    // init_pair(0, COLOR_BLACK, COLOR_BLACK);
    // init_pair(1, COLOR_BLACK, COLOR_CYAN);
    // attron(COLOR_PAIR(1));
    // // mvprintw(getWindowSize().y / 2, getWindowSize().x / 2, "              ");
    // mvprintw(getWindowSize().y / 2, getWindowSize().x / 2 - 15, "                                     ");
    // mvprintw(0, 0, "                                     ");
    // attroff(COLOR_PAIR(1));
    refresh();



    // attr_t att;
    // NCURSES_PAIRS_T pair;
    // short fg;
    // short bg;
    // auto winSize = getWindowSize();
    // for (unsigned int y = 0; y < winSize.y; ++y) {
    //     log() << "[";
    //     for (unsigned int x = 0; x < winSize.x; ++x) {
    //         move(y, x);
    //         attr_get(&att, &pair, NULL);
    //         pair_content(att, &fg, &bg);
    //         log() << (x == 0 ? "" : ", ") << pair;
    //         // log() << "[" << att << ", " << pair << ", " << fg << ", " << bg << "]" << std::endl;
    //     }
    //     log() << "]" << std::endl;
    // }
    restartClock();
}

void LibNCRS::stop()
{
    endwin();
    std::cout << "Stop" << std::endl;
}

void LibNCRS::clearWindow()
{
    erase();
}

void LibNCRS::display()
{
    if (!_eventFetched) {
        getch();
    }
    refresh();
    // Add some wait to normalise frames
    // attr_t att;
    // NCURSES_PAIRS_T pair;
    // short fg;
    // short bg;
    // auto winSize = getWindowSize();
    // for (unsigned int y = 0; y < winSize.y; ++y) {
    //     log() << "[";
    //     for (unsigned int x = 0; x < winSize.x; ++x) {
    //         move(y, x);
    //         attr_get(&att, &pair, NULL);
    //         pair_content(att, &fg, &bg);
    //         log() << (x == 0 ? "" : ", ") << pair;
    //         // log() << "[" << att << ", " << pair << ", " << fg << ", " << bg << "]" << std::endl;
    //     }
    //     log() << "]" << std::endl;
    // }
    restartClock();
    _eventFetched = false;
}

void LibNCRS::restartClock()
{
    _timePoint = std::chrono::high_resolution_clock::now();
}

double LibNCRS::getDeltaTime()
{
    return std::chrono::duration_cast
        <
        std::chrono::duration<double, std::ratio<1>>
        >
            (std::chrono::high_resolution_clock::now() - _timePoint).count();
}

arcade::data::Vector2u LibNCRS::getWindowSize()
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
                printw("So yes there is a mov");
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
    auto &t = reinterpret_cast<std::unique_ptr<TextNCRS> &>(text);
    auto pos = t->getPosition();
    auto org = t->getOrigin();
    // init_color(1, t->getNcrsColor())
    const char *content = t->getString();
    unsigned int size = t->getText().size();
    move(pos.y - org.y, pos.x - org.x);
    attr_t att;
    NCURSES_PAIRS_T pair;
    short fg;
    short bg;
    for (unsigned int i = 0; i < size; ++i, ++content) {
        attr_get(&att, &pair, NULL);
        pair_content(att, &fg, &bg);
        pair = getNcrsColorPair(t->getNcrsColor(), bg);
        addch(*content | COLOR_PAIR(pair));
    }
    // init_pair(t->getNcrsColorPair(), t->getNcrsColor(), bg);
    // attron(COLOR_PAIR(t->getNcrsColorPair()));
    // printw("%s", t->getString());
    // attroff(COLOR_PAIR(t->getNcrsColorPair()));
    // static int i = 0;
    // mvprintw(i++, 0, "Fg %d Bg %d", fg, bg);


    // static int tmp = 3;
    // auto events = getEvents();
    // if (events.size()) {
    //     mvprintw(tmp++, 0, "%d", events.size());
    //     for (unsigned int i = 0; i < events.size(); ++i) {
    //         printw(" [%d, %d, %d, %d]", events[i].type, events[i].btn, events[i].x, events[i].y);
    //     }
    // }
}

void LibNCRS::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    auto &s = reinterpret_cast<std::unique_ptr<SpriteNCRS> &>(sprite);
    auto &img = s->getSprite();
    for (auto &line : img) {
        for (auto &pixel : line) {
            log() << (char)pixel;
        }
        log() << std::endl;
    }
}

std::unique_ptr<arcade::displayer::IText> LibNCRS::createText()
{
    return std::make_unique<TextNCRS>();
}

std::unique_ptr<arcade::displayer::IText> LibNCRS::createText(const std::string &text)
{
    return std::make_unique<TextNCRS>(text);
}

std::unique_ptr<arcade::displayer::ISprite> LibNCRS::createSprite()
{
    return std::make_unique<SpriteNCRS>();
}

std::unique_ptr<arcade::displayer::ISprite> LibNCRS::createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
{
    (void)spritePath;
    return std::make_unique<SpriteNCRS>(asciiSprite, scale);
}

NCURSES_PAIRS_T LibNCRS::getNcrsColorPair(short fg, short bg)
{
    static std::array<std::tuple<short, short, NCURSES_PAIRS_T>, 3> cache;
    static std::vector<std::tuple<short, short, short>> pairs;

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