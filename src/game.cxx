#include "game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

#include "inputhandler.hpp"
#include "texturemanager.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "menustate.hpp"
#include "mainmenustate.hpp"
#include "playstate.hpp"
#include "menubutton.hpp"
#include "animatedgraphic.hpp"

Game *Game::s_pInstance = 0;

Game::Game()
{
}

Game::~Game()
{
}

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        int flags = SDL_WINDOW_SHOWN;
        if (fullscreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }

        m_gameWidth = width;
        m_gameHeight = height;

        TheInputHandler::Instance()->initialiseJoysticks();
        TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
        TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
        TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
        TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0)
            {
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false;
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false;
    }

    std::cout << "init success\n";
    m_bRunning = true;

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    m_pGameStateMachine->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();

    // if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    // {
    //     m_pGameStateMachine->changeState(new PlayState());
    // }
}

void Game::clean()
{
    std::cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::quit()
{
    m_bRunning = false;
}