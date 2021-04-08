/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-honore.dupieu
** File description:
** init
*/

#include "Arcade.hpp"

static constexpr int calulateStartY(int startPoint, unsigned int yOffset, unsigned int characterSize, unsigned int nbElem)
{
    startPoint -= ((nbElem / 2) * characterSize) + ((nbElem / 2) * yOffset);
    startPoint += ((!(nbElem % 2)) * (yOffset / 2));
    startPoint -= ((nbElem % 2) * (characterSize / 2));
    return startPoint;
}

void arcade::Arcade::menuLoadDisplayer()
{
    _menuBoxes.clear();
    std::string font{"ressources/font.ttf"};
    arcade::data::FloatRect rect;

    auto winSize = _displayer->getWindowSize();
    const int yOffset = winSize.y * 0.02f;
    int characterSize = isOptions(_displayer, SET_CHARACTER_SIZE) ? 20 : 1;
    int yStart = calulateStartY(winSize.y / 2, yOffset, characterSize, _galibsPath.size());
    arcade::data::Vector2f pos{static_cast<float>(winSize.x / 2), static_cast<float>(yStart)};
    arcade::data::Vector2f boxMarigin;
    boxMarigin.y = ((2 + (2 * !!(characterSize - 1))) * yOffset) + (yOffset < 1 ? 2 : 0);
    boxMarigin.x = ((3 + (2 * !!(characterSize - 1))) * yOffset) + (yOffset < 1 ? 2 : 0);

    // --- Games List ---
    _menuGamesListText.clear();
    unsigned int longestWidth = 0;
    for (unsigned int i = 0; i < _galibsPath.size(); ++i, pos.move(0, yOffset + characterSize)) {
        std::string game = _galibsPath[i];
        std::size_t it = game.find_last_of('/');
        if (it != std::string::npos && ++it < game.size()) {
            game = game.substr(it);
        }
        longestWidth = game.size() > longestWidth ? game.size() : longestWidth;
        _menuGamesListText.push_back(_displayer->createText(game));
        auto &text = _menuGamesListText[i];
        text->setCharacterSize(characterSize);
        text->setFont(font);
        text->setOrigin({text->getLocalBounds().width / 2, 0});
        text->setPosition(pos);
    }
    _menuGamesListText[_menuSelectedGame]->setColor(arcade::data::Color::Cyan);



    // --- High Scores ---
    const unsigned int highScorePrint = 3;
    yStart = calulateStartY(winSize.y / 2, yOffset, characterSize, highScorePrint);
    pos = {static_cast<float>(winSize.x * 0.15f), static_cast<float>(yStart)};

    _menuHighScoreText = _displayer->createText("High Scores:");
    _menuHighScoreText->setCharacterSize(characterSize);
    _menuHighScoreText->setFont(font);
    _menuHighScoreText->setOrigin({_menuHighScoreText->getLocalBounds().width / 2, 0});
    _menuHighScoreText->setPosition(pos + arcade::data::Vector2i{0, -(yOffset * 2 + characterSize)});
    
    _menuHighScoresText.clear();
    for (unsigned int i = 0; i < highScorePrint; ++i, pos.move(0, yOffset + characterSize)) {
        _menuHighScoresText.push_back(_displayer->createText("score"));
        auto &t = _menuHighScoresText[_menuHighScoresText.size() - 1];
        t->setCharacterSize(characterSize);
        t->setFont(font);
        t->setPosition(pos);
    }
    menuSetHighScoresText();

    rect.top = _menuHighScoreText->getPosition().y - ((2 + (2 * !!(characterSize - 1))) * yOffset) - (yOffset < 1 ? 2 : 0);
    rect.left = _menuHighScoreText->getPosition().x - _menuHighScoreText->getOrigin().x - ((3 + (2 * !!(characterSize - 1))) * yOffset) - (yOffset < 1 ? 2 : 0);
    rect.height = (_menuHighScoresText[_menuHighScoresText.size() - 1]->getPosition().y + characterSize + ((2 + (2 * !!(characterSize - 1))) * yOffset)) + (yOffset < 1 ? 2 : 0) - rect.top;
    rect.width = (pos.x + (20 * characterSize)) + 2 + (yOffset < 1 ? 1 : 0) - rect.left;
    menuCreateBox(rect);



    // --- Graphic Lib List ---
    yStart = calulateStartY(winSize.y / 2, yOffset, characterSize, _grlibsPath.size());
    pos = {static_cast<float>(winSize.x * 0.75f), static_cast<float>(yStart)};
    
    _menuGrListText.clear();
    longestWidth = 0;
    for (unsigned int i = 0; i < _grlibsPath.size(); ++i, pos.move(0, yOffset + characterSize)) {
        std::string grlib = _grlibsPath[i];
        std::size_t it = grlib.find_last_of('/');
        if (it != std::string::npos && ++it < grlib.size()) {
            grlib = grlib.substr(it);
        }
        _menuGrListText.push_back(_displayer->createText(grlib));
        auto &t = _menuGrListText[_menuGrListText.size() - 1];
        t->setCharacterSize(characterSize);
        t->setFont(font);
        t->setPosition(pos);
        auto size = t->getLocalBounds().width;
        longestWidth = size > longestWidth ? size : longestWidth;
    }

    rect.top = _menuGrListText[0]->getPosition().y - boxMarigin.y;
    rect.left = _menuGrListText[0]->getPosition().x - _menuGrListText[0]->getOrigin().x - boxMarigin.x;
    rect.height = _menuGrListText[_menuGrListText.size() - 1]->getPosition().y + characterSize + (boxMarigin.y * 1) - rect.top;
    rect.width = longestWidth + (boxMarigin.x * 2);
    menuCreateBox(rect);



    // --- New Game With Name Input ---
    _menuNewGameText = _displayer->createText("New Game");
    _menuNewGameText->setCharacterSize(characterSize);
    _menuNewGameText->setFont(font);
    _menuNewGameText->setPosition({_menuHighScoreText->getPosition().x - _menuHighScoreText->getOrigin().x, winSize.y * 0.80f});
    _menuAskPlayerNameText = _displayer->createText("Enter player name: ");
    _menuAskPlayerNameText->setCharacterSize(characterSize);
    _menuAskPlayerNameText->setFont(font);
    _menuAskPlayerNameText->setPosition({_menuNewGameText->getPosition().x + yOffset, _menuNewGameText->getPosition().y + (yOffset * 2) + characterSize});
    _menuPlayerNameText = _displayer->createText("________");
    _menuPlayerNameText->setCharacterSize(characterSize);
    _menuPlayerNameText->setFont(font);
    _menuPlayerNameText->setPosition({_menuAskPlayerNameText->getPosition().x + _menuAskPlayerNameText->getLocalBounds().width,
                                        _menuAskPlayerNameText->getPosition().y});

    rect.top = _menuNewGameText->getPosition().y - boxMarigin.y;
    rect.left = _menuNewGameText->getPosition().x - boxMarigin.x;
    rect.height = _menuAskPlayerNameText->getPosition().y + boxMarigin.x - rect.top;
    rect.width = _menuAskPlayerNameText->getLocalBounds().width + _menuPlayerNameText->getLocalBounds().width + (boxMarigin.x * 2);
    menuCreateBox(rect, '+', '-', '|');
    auto name = _playerName;
    for (unsigned int i = name.size(); i < 8; ++i, name.push_back('_'));
    _menuPlayerNameText->setText(name);



    // --- Keys Instructions ---
    _menuInstructions.clear();
    _menuInstructions.push_back(_displayer->createText("'/': Previous graphics library."));
    _menuInstructions.push_back(_displayer->createText("'*': Next graphics library."));
    _menuInstructions.push_back(_displayer->createText("'8': Previous game."));
    _menuInstructions.push_back(_displayer->createText("'9': Next game."));
    _menuInstructions.push_back(_displayer->createText("'-': Restart the game."));
    _menuInstructions.push_back(_displayer->createText("Esc: Go back to the menu."));
    _menuInstructions.push_back(_displayer->createText("Esc: Exit."));
    characterSize = isOptions(_displayer, SET_CHARACTER_SIZE) ? 10 : 1;
    boxMarigin.y = ((2 + (2 * !!(characterSize - 1))) * yOffset) + (yOffset < 1 ? 2 : 0);
    boxMarigin.x = ((3 + (2 * !!(characterSize - 1))) * yOffset) + (yOffset < 1 ? 2 : 0);
    pos = {winSize.x * 0.80f, winSize.y * 0.75f};
    rect.left = pos.x - (boxMarigin.x * (1 - (0.4 * !!(characterSize - 1))));
    rect.top = pos.y - (boxMarigin.y * (1 - (0.35 * !!(characterSize - 1))));
    longestWidth = 0;
    for (auto &ins : _menuInstructions) {
        ins->setCharacterSize(characterSize);
        ins->setFont(font);
        ins->setPosition(pos);
        auto size = ins->getLocalBounds().width;
        longestWidth = size > longestWidth ? size : longestWidth;
        pos.move(0, characterSize + yOffset);
    }
    rect.width = longestWidth + (2 * (boxMarigin.x * (1 - (0.4 * !!(characterSize - 1)))));
    rect.height = _menuInstructions[_menuInstructions.size() - 1]->getPosition().y + _menuInstructions[_menuInstructions.size() - 1]->getLocalBounds().height + (boxMarigin.y * (1 - (0.5 * !!(characterSize - 1)))) - rect.top;
    arcade::data::Vector2f move{winSize.x * 0.98f - (rect.left + rect.width), winSize.y * 0.98f - (rect.top + rect.height)};
    rect.top += move.y;
    rect.left += move.x;
    for (auto &ins : _menuInstructions) {
        ins->setPosition(ins->getPosition() + move);
    }
    menuCreateBox(rect);
}

void arcade::Arcade::menuCreateBox(arcade::data::FloatRect rect, char corners, char horizontal, char vertical, char fill)
{
    menuCreateBox(rect, corners, horizontal, horizontal, vertical, vertical, fill);
}

void arcade::Arcade::menuCreateBox(arcade::data::FloatRect rect, char corners, char top, char bottom, char left, char right, char fill)
{
    std::vector<std::string> asciiScoreBoard;
    unsigned int asciiYlimit = rect.height;
    unsigned int asciiXlimit = rect.width;
    asciiScoreBoard.reserve(asciiYlimit);
    for (float y = 0; y < asciiYlimit; ++y) {
        std::string line;
        line.reserve(asciiXlimit);
        for (float x = 0; x < asciiXlimit; ++x) {
            char c;
            if ((!x && (!y || y == (asciiYlimit - 1))) || (x == (asciiXlimit - 1) && (!y || y == (asciiYlimit - 1)))) {
                c = corners;
            } else if (!y) {
                c = top;
            } else if (y == (asciiYlimit - 1)) {
                c = bottom;
            } else if (!x) {
                c = left;
            } else if (x == (asciiXlimit - 1)) {
                c = right;
            } else {
                c = fill;
            }
            line.push_back(c);
        }
        asciiScoreBoard.push_back(line);
    }
    _menuBoxes.push_back(_displayer->createSprite("ressources/board.bmp", asciiScoreBoard));
    auto &p = _menuBoxes[_menuBoxes.size() - 1];
    p->setScale(arcade::data::Vector2f{rect.width / p->getLocalBounds().width, rect.height / p->getLocalBounds().height});
    p->setPosition(arcade::data::Vector2f{rect.left, rect.top});
}

void arcade::Arcade::menuSetHighScoresText()
{
    unsigned int i = 0;
    for (auto &t : _menuHighScoresText) {
        std::string score{std::to_string(i + 1) + "."};
        if (i < _highScores[_menuSelectedGame].size()) {
            score += " " + _highScores[_menuSelectedGame][i].first + ": " + std::to_string(_highScores[_menuSelectedGame][i].second);
        }
        t->setText(score);
        ++i;
    }
}