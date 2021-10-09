#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <vector>
#include "menustate.hpp"
#include "gameobject.hpp"

class MainMenuState : public MenuState
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

    virtual void setCallbacks(const std::vector<Callback> &callbacks);

private:
    static const std::string s_menuID;

    std::vector<GameObject *> m_gameObjects;
};

#endif
