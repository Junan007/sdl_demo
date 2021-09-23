#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "gameobject.hpp"
#include "vector2d.hpp"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    std::string m_textureID;
};

#endif