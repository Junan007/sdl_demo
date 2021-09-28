#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include "gamestate.hpp"

class MenuState: public GameState
{
protected:
    typedef void(*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

#endif
