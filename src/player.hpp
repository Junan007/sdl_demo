#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.hpp"

class Player: public GameObject
{
public:
    void load(int x, int y, int width, int height, std::string textureID);
    void daraw(SDL_Renderer* pRenderer);
    void update();
    void clean();
};

#endif