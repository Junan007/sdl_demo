#include "inputhandler.hpp"
#include <iostream>
#include "game.hpp"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
    for(int i = 0; i < 3; i++)
    {
        m_mouseButtonStates.push_back(false);
    }
    m_mousePosition = new Vector2D(0, 0);

    int numKey = 0;
    SDL_GetKeyboardState(&numKey);
    m_keystate = new Uint8[numKey];
    printf("numKey: %d\n", numKey);
}

void InputHandler::initialiseJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0) 
    {
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if (joy != NULL)
            {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));

                std::vector<bool> tempButtons;
                for (int j = 0;j < SDL_JoystickNumButtons(joy); j++)
                {
                    tempButtons.push_back(false);
                }
                m_buttonStates.push_back(tempButtons);
            } else {
                std::cout << SDL_GetError();
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);        
        m_bJoystickInitialised = true;
    } else {
        m_bJoystickInitialised = false;
    }
    std::cout << "Initialised " << m_joysticks.size() << " joystick(s)\n";
}

void InputHandler::update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            TheGame::Instance()->quit();
        } 
        
        if (event.type == SDL_JOYAXISMOTION) {
            onJoystickAxisMove(event);    
        } 
        
        if (event.type == SDL_JOYBUTTONDOWN) {
            onJoystickButtonDown(event);
        } 
        
        if (event.type == SDL_JOYBUTTONUP) {
            onJoystickButtonUp(event);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            onMouseButtonDown(event);
        }
        
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            onMouseButtonUp(event);
        }

        if (event.type == SDL_MOUSEMOTION) 
        {
            onMouseMove(event);
        }

        if (event.type == SDL_KEYDOWN) {
            onKeyDown();
        }

        if (event.type == SDL_KEYUP) {
            onKeyUp();
        }
    }
}

void InputHandler::clean()
{
    if (m_bJoystickInitialised) {
        for(unsigned int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

int InputHandler::xvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0)
    {
        if (stick == 1) {
            return m_joystickValues[joy].first->getX();
        } else if (stick == 2) {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0)
    {
        if (stick == 1) {
            return m_joystickValues[joy].first->getY();
        } else if (stick == 2) {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystate != 0) {
        if (m_keystate[key] == 1)
        {
            return true;
        } else {
            return false;
        }
    }
    return false;
}


void InputHandler::onKeyDown()
{
    m_keystate = (Uint8*)(SDL_GetKeyboardState(0));
}

void InputHandler::onKeyUp()
{
    m_keystate = (Uint8*)(SDL_GetKeyboardState(0));
}

void InputHandler::onMouseMove(SDL_Event& event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);  
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = true;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = true;
    }
}
void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtonStates[LEFT] = false;
    }
    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    if (event.jaxis.axis == 0)
    {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(1);   
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(-1);
        } else {
            m_joystickValues[whichOne].first->setX(0);
        }
    }

    if (event.jaxis.axis == 1)
    {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(1);   
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(-1);
        } else {
            m_joystickValues[whichOne].first->setY(0);
        }
    }

    if (event.jaxis.axis == 3)
    {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(1);   
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(-1);
        } else {
            m_joystickValues[whichOne].second->setX(0);
        }
    }

    if (event.jaxis.axis == 4)
    {
        if (event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(1);   
        } else if (event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(-1);
        } else {
            m_joystickValues[whichOne].second->setY(0);
        }
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = false;
}