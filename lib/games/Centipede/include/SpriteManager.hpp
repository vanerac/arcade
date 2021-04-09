/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** SpriteManager.hpp.h file
*/

#ifndef B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_SPRITEMANAGER_HPP
#define B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_SPRITEMANAGER_HPP

#include <Games.hpp>

enum orientation {
    STATIC, // todo ?
    UP,
    RIGHT,
    RIGHT_DOWN,
    LEFT,
    LEFT_DOWN,
    DOWN
};

class SpriteManager  {
    public:
    SpriteManager(std::shared_ptr<arcade::displayer::IDisplay> &disp, int
    level = 1);
    ~SpriteManager();

    void change_level(int level);

    std::unique_ptr<arcade::displayer::ISprite> getCentipedeHead
    (orientation) const;
    std::unique_ptr<arcade::displayer::ISprite> getCentipedeBody
    (orientation) const;
    std::unique_ptr<arcade::displayer::ISprite> getObstacle(int health) const;
    std::unique_ptr<arcade::displayer::ISprite> getPlayer() const;
    std::unique_ptr<arcade::displayer::ISprite> getShot() const;
    std::unique_ptr<arcade::displayer::IText> getText(std::string &text)
    const;


    private:
    int _level;
    std::shared_ptr<arcade::displayer::IDisplay> displayer;
    std::unique_ptr<arcade::displayer::ISprite> _spriteSheet;

};

#endif //B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_SPRITEMANAGER_HPP
