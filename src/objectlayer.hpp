#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H
#include <vector>
#include "layer.hpp"
#include "gameobject.hpp"

class ObjectLayer : public Layer
{
public:
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects()
    {
        return &m_gameObjects;
    }
private:
    std::vector<GameObject*> m_gameObjects;
};

#endif
