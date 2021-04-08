/*
** EPITECH PROJECT, 2021
** ${FOLDER_NAME}
** File description:
** Entities.hpp.h file
*/

#ifndef B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_ENTITIES_HPP
#define B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_ENTITIES_HPP

#include <vector>
#include "SpriteManager.hpp"

struct Position {
    int x;
    int y;
};

class Entity {
    public:
    Entity(int health);
    ~Entity();
    void setPosition(int x, int y);
    struct Position getPosition() const;
    void setHealth(int health);
    int getHealth() const;
    void draw(std::shared_ptr<arcade::displayer::IDisplay> &disp);
    void setSprite(std::unique_ptr<arcade::displayer::ISprite> sprite);
    std::unique_ptr<arcade::displayer::ISprite> getSprite() const;

    protected:
    struct Position pos;
    int health;

    std::unique_ptr<arcade::displayer::ISprite> sprite;

};

class CentipedeEntity : public Entity {
    public:
        CentipedeEntity(int size);
        ~CentipedeEntity();
        void setTiles(const std::vector<Entity *>& tiles);
        std::vector<Entity*> getTiles() const;
        CentipedeEntity *splitAt(int tileIndex);
        void move();
        orientation getOrientation();
        void getOrientation(orientation);
    private:
        std::vector<Entity*> _tiles;
        orientation orientation;
};

#endif //B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_ENTITIES_HPP
