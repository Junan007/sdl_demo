#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include "gamestate.hpp"
#include "sdlgameobject.hpp"
#include "level.hpp"

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID; }

private:
    bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);

private:
    static const std::string s_playID;
    std::vector<GameObject *> m_gameObjects;

    Level *m_pLevel;
};

#endif