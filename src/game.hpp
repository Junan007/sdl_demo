#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>
#include <vector>
#include "gameobject.hpp"
#include "gamestatemachine.hpp"

class Game {
public:
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void render();
    void update();
    void handleEvents();
    void clean();

    void quit();

    bool running() { return m_bRunning; }

    SDL_Renderer* getRenderer() const { return m_pRenderer; }

    static Game* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }

    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
private:
    Game();

private:
    bool m_bRunning;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    static Game* s_pInstance;
    std::vector<GameObject*> m_gameObjects;

    GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;

#endif
