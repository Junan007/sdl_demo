#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <vector>
#include <SDL2/SDL.h>

#include "vector2d.hpp"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

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

    bool getMouseButtonState(int buttonNumber)
    {
        return m_mouseButtonStates[buttonNumber];
    }

    Vector2D* getMousePosition()
    {
        return m_mousePosition;
    }

    bool isKeyDown(SDL_Scancode key);
private:
    InputHandler();
    ~InputHandler() {}

    void onKeyDown();
    void onKeyUp();
    
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);
    
private:
    static InputHandler* s_pInstance;

    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoystickInitialised;

    static const int m_joystickDeadZone = 10000;
    std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;

    std::vector<std::vector<bool> > m_buttonStates;
    std::vector<bool> m_mouseButtonStates;

    Vector2D* m_mousePosition;

    Uint8* m_keystate;
};

typedef InputHandler TheInputHandler;

#endif