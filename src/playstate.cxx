#include "playstate.hpp"
#include <iostream>
#include "gameobject.hpp"
#include "texturemanager.hpp"
#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "inputhandler.hpp"
#include "pausestate.hpp"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }

    for (int i = 0;i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PlayState::render()
{
    for (int i = 0;i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    std::cout << "entering PlayState\n";
    if (!TheTextureManager::Instance()->load("./assets/arrow.png", "arrow", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TheTextureManager::Instance()->load("./assets/helicopter2.png", "hilicopter2", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "arrow"));
    GameObject* enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "hilicopter2"));
    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);

    printf("PlayState::OnEnter finished.\n");

    return true;
}

bool PlayState::onExit()
{
    std::cout << "exiting PlayState\n";
    for (int i = 0 ;i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");

    return true;
}