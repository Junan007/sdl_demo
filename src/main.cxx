#include <SDL2/SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* arggs[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        printf("SDL_Init success.\n");
        g_pWindow = SDL_CreateWindow("Chapter 1: Setting up SDL",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_SHOWN
            );
        
        if (g_pWindow != 0) 
        {
            printf("g_pWindow is not null.\n");
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        } else {
            printf("g_pWindow is null.\n");
        }
    } else {
        printf("SDL_Init error.\n");
        return 1;
    }

    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(g_pRenderer);

    SDL_RenderPresent(g_pRenderer);
    
    SDL_Delay(5000);
    SDL_Quit();

    printf("OK\n");
    return 0;
}