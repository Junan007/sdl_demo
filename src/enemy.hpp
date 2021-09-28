#ifndef ENEMY_H
#define ENEMY_H

#include "sdlgameobject.hpp"
#include "gameobjectfactory.hpp"

class Enemy: public SDLGameObject
{
public:
    Enemy();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);
};

class EnemyCreator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const
    {
        return new Enemy();
    }
};

#endif