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
        virtual void draw(std::shared_ptr<arcade::displayer::IDisplay> &disp);
        void setSprite(std::unique_ptr<arcade::displayer::ISprite> sprite);
        std::unique_ptr<arcade::displayer::ISprite> &getSprite();
        bool does_collide(std::unique_ptr<Entity> &target);
        orientation getOrientation() const;
        void setOrientation(enum orientation orientation);

        virtual void move();
        void setVelocity(float velocity);
        float getVelocity() const;

        struct Position pos; // todo change this

    protected:
        int health;
        std::unique_ptr<arcade::displayer::ISprite> _sprite;
        enum orientation _orientation = STATIC;
        float velocity;

};

class CentipedeEntity : public Entity {
    public:
        CentipedeEntity(int size);
        ~CentipedeEntity();
        void setTiles(std::vector<std::unique_ptr<Entity>> tiles);
        std::vector<std::unique_ptr<Entity>> &getTiles();
        std::unique_ptr<CentipedeEntity> splitAt(int tileIndex);
        void move() override;
        void draw(std::shared_ptr<arcade::displayer::IDisplay> &disp) override;


    private:
        std::vector<std::unique_ptr<Entity>> _tiles;

};

#endif //B_OOP_400_BDX_4_1_ARCADE_HONORE_DUPIEU_ENTITIES_HPP
