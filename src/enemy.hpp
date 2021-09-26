#ifndef ENEMY_H
#define ENEMY_H

#include "sdlgameobject.hpp"

class Enemy: public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
private:
    int m_numFrames;
};

#endif