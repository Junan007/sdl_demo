#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <vector>
#include <SDL2/SDL.h>

#include "vector2d.hpp"

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if (s_pInstance == 0) {
            s_pInstance = new InputHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }

    void update();
    void clean();
    void initialiseJoysticks();

    bool joysticksInitialised() {
        return m_bJoystickInitialised;
    }

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }
private:
    InputHandler();
    ~InputHandler() {}
    
private:
    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoystickInitialised;

    static const int m_joystickDeadZone = 10000;
    std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;

    std::vector<std::vector<bool> > m_buttonStates;    
};

typedef InputHandler TheInputHandler;

#endif