#include "pausestate.hpp"

#include "game.hpp"
#include "texturemanager.hpp"
#include "mainmenustate.hpp"
#include "menubutton.hpp"
#include "inputhandler.hpp"
#include "stateparser.hpp"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PauseState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter()
{
    std::cout << "entering PauseState\n";
    StateParser stateParser;
    stateParser.parseState("pause.xml", s_pauseID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    setCallbacks(m_callbacks);

    return true;
}

bool PauseState::onExit()
{
    std::cout << "exiting PauseState\n";

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    for (int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    // TheInputHandler::Instance()->reset();
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback> &callbacks)
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