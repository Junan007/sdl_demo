#ifndef _GAME_H_
#define _GAME_H_

#include <SDL2/SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

    void render();
    void update();
    void handleEvents();
    void clean();

    bool running() { return m_bRunning;}
private:
    bool m_bRunning;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    SDL_Texture* m_
};

#endif
