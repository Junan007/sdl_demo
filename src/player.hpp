#ifndef PLAYER_H
#define PLAYER_H

#include "sdlgameobject.hpp"
#include "gameobjectfactory.hpp"

class Player: public SDLGameObject
{
public:
    Player();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);
private:
    void handleInput();
};

class PlayerCreator : public BaseCreator
{
public:
    GameObject* createGameObject()
    {
        return new Player();
    }
};

#endif