#include "playstate.hpp"
#include <iostream>
#include "gameobject.hpp"
#include "texturemanager.hpp"
#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "inputhandler.hpp"
#include "pausestate.hpp"
#include "gameoverstate.hpp"

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

    if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
    {
        TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
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

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA < leftB) return false;
    if (leftA >= rightB) return false;

    return true;
}