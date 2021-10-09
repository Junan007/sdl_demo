#include "gameoverstate.hpp"
#include "game.hpp"
#include "texturemanager.hpp"
#include "mainmenustate.hpp"
#include "playstate.hpp"
#include "animatedgraphic.hpp"
#include "menubutton.hpp"
#include "stateparser.hpp"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
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
    std::cout << "entering PauseState\n";
    StateParser stateParser;
    stateParser.parseState("over.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    setCallbacks(m_callbacks);

    return true;
}

bool GameOverState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    for (int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks)
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (dynamic_cast<MenuButton *>(m_gameObjects[i]))
        {
            MenuButton *pButton = dynamic_cast<MenuButton *>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}