#include "game.hpp"
#include <iostream>

Game::Game() 
{

}

Game::~Game() 
{
    
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        int flags = SDL_WINDOW_SHOWN;
        if (fullscreen) {
            flags = SDL_WINDOW_FULLSCREEN;
        }

        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0) {
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

                SDL_Surface* pTmpSurface = SDL_LoadBMP("./assets/rider.bmp");
                m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTmpSurface);
                SDL_FreeSurface(pTmpSurface);

                SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
                m_destinationRectangle.x = m_sourceRectangle.x = 0;
                m_destinationRectangle.y = m_sourceRectangle.y = 0;
                m_destinationRectangle.w = m_sourceRectangle.w;
                m_destinationRectangle.h = m_sourceRectangle.h;
            } else {
                std::cout << "renderer init fail\n";
                return false;
            }
        } else {
            std::cout << "window init fail\n";
            return false;    
        }
    } else {
        std::cout << "SDL init fail\n";
        return false;
    }

    std::cout << "init success\n";
    m_bRunning = true;
    return true;
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{

}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        m_bRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}