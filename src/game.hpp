#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <vector>
#include "gameobject.hpp"
#include "player.hpp"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() { return m_bRunning;}
private:
    bool m_bRunning;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    GameObject* m_player1;
    GameObject* m_enemy1;
    GameObject* m_enemy2;
    GameObject* m_enemy3;

    std::vector<GameObject*> m_gameObjects;
};

#endif
