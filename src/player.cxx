#include "player.hpp"

#include <SDL2/SDL.h>
#include "inputhandler.hpp"

Player::Player()
{
    
}

void Player::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);

    handleInput();

    m_currentFrame = 0;//int(((SDL_GetTicks() / 100) % 6));
    SDLGameObject::update();
}

void Player::clean()
{
    SDLGameObject::clean();
}

void Player::handleInput()
{
    /*if (TheInputHandler::Instance()->joysticksInitialised())
    {
        if (TheInputHandler::Instance()->xvalue(0, 1) > 0 ||
            TheInputHandler::Instance()->xvalue(0, 1) < 0)
            {
                m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
            }
        
        if (TheInputHandler::Instance()->yvalue(0, 1) > 0 || 
            TheInputHandler::Instance()->yvalue(0, 1) < 0)
            {
                m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
            }
        
        if (TheInputHandler::Instance()->xvalue(0, 2) > 0 ||
            TheInputHandler::Instance()->xvalue(0, 2) < 0) {
                m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
            }
        
        if (TheInputHandler::Instance()->yvalue(0, 2) > 0 || 
            TheInputHandler::Instance()->yvalue(0, 2))
            {
                m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
            }
        
        if (TheInputHandler::Instance()->getButtonState(0, 3))
        {
            m_velocity.setX(1);
        }        
    }

    if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
    {
        m_velocity.setX(1);
    }

    Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    m_velocity = (*vec - m_position) / 100;

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_velocity.setX(2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        m_velocity.setX(-2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        m_velocity.setY(2);
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        m_velocity.setY(-2);
    }*/

    Vector2D* target = TheInputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}