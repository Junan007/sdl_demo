#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H

#include "sdlgameobject.hpp"
#include "gameobjectfactory.hpp"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(const LoaderParams* pParams);
private:
    int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:
    virtual GameObject* createGameObject() const
    {
        return dynamic_cast<GameObject*>(new AnimatedGraphic());
    }
};

#endif