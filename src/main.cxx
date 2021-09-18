#include "game.hpp"

int main(int argc, char* argv[])
{
    Game* game = new Game();
    if (game->init("Chapter 1: Settting up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false))
    {
        while (game->running()) 
        {
            game->handleEvents();
            game->update();
            game->render();
        }
    }

    game->clean();
    delete game;
    return 0;
}