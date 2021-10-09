#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "sdlgameobject.hpp"
#include "gameobjectfactory.hpp"

class MenuButton : public SDLGameObject
{
public:
    MenuButton();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams *pParams);

    void setCallback(void (*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }

private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    bool m_bReleased;

    int m_callbackID;
};

class MenuButtonCreator : public BaseCreator
{
public:
    virtual GameObject *createGameObject() const
    {
        return dynamic_cast<GameObject *>(new MenuButton());
    }
};

#endif
