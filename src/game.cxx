#include "game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "texturemanager.hpp"

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
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
                if (!TheTextureManager::Instance()->load("./assets/animate-alpha.png", "animate", m_pRenderer)) {
                    return false;
                }
                
                m_go.load(100, 100, 128, 82, "animate");
                m_player.load(300, 300, 128, 82, "animate");
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
    SDL_RenderClear(m_pRenderer);
    m_go.draw(m_pRenderer);
    m_player.draw(m_pRenderer);    
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_go.update();
    m_player.update();
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