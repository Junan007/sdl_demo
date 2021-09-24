#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include "gamestate.hpp"
#include "gameobject.hpp"

class MenuState: public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_menuID; }
private:
    static void s_menuToPlay();
    static void s_exitFromMenu();
private:
    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;
};

#endif
