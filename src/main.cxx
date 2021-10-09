#include "game.hpp"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char *argv[])
{
    Uint32 frameStart, frameTime;
    if (TheGame::Instance()->init("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false))
    {
        std::cout << "game init success!\n";
        while (TheGame::Instance()->running())
        {
            frameStart = SDL_GetTicks();
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();
    return 0;
}