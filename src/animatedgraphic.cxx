#include "animatedgraphic.hpp"

#include <SDL2/SDL.h>

AnimatedGraphic::AnimatedGraphic()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
    SDLGameObject::clean();
}
