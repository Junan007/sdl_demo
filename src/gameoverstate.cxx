#include "gameoverstate.hpp"
#include "game.hpp"
#include "texturemanager.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}


void GameOverState::update()
{

}

void GameOverState::render()
{

}

bool GameOverState::onEnter()
{
    if (!TheTextureManager::Instance()->load("./assets/gameover.png", "gameovertext", TheGame::Instance()->getRenderer()))
    {
        return false;
    } 

    if (!TheTextureManager::Instance()->load("./assets/main.png", "mainbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    } 

    if (!TheTextureManager::Instance()->load("./assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    
}

bool GameOverState::onExit()
{

}

