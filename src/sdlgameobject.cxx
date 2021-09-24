#include "sdlgameobject.hpp"

#include "texturemanager.hpp"
#include "game.hpp"

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
: GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();

    m_textureID = pParams->getTextureID();
    m_currentRow = 0;//1;
    m_currentFrame = 1;
}

void SDLGameObject::draw()
{
    SDL_RendererFlip flag = SDL_FLIP_NONE;
    if (m_velocity.getX() > 0)
    {
        flag = SDL_FLIP_HORIZONTAL;
    }

    TextureManager::Instance()->drawFrame(m_textureID, 
                                          int(m_position.getX()), 
                                          int(m_position.getY()), 
                                          m_width, 
                                          m_height, 
                                          m_currentRow, 
                                          m_currentFrame, 
                                          TheGame::Instance()->getRenderer(),
                                          flag);
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean()
{

}