#ifndef PLAYER_H
#define PLAYER_H

#include "sdlgameobject.hpp"

class Player: public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
private:
    void handleInput();
};

#endif