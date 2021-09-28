#include "mainmenustate.hpp"

#include <iostream>
#include "texturemanager.hpp"
#include "game.hpp"
#include "menubutton.hpp"
#include "playstate.hpp"
#include "stateparser.hpp"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    std::cout << "entering MainMenuState\n";

    StateParser stateParser;
    stateParser.parseState("menu.xml", s_menuID, &m_gameObjects, &m_textureIDList);
    std::cout << "xxxx\n";

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);
    std::cout << "MainMenuState::onEnter finished.\n";
    return true;
}

bool MainMenuState::onExit()
{
    std::cout << "exiting MenuState\n";

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

void MainMenuState::s_menuToPlay()
{
    std::cout << "Play button clicked\n";
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked\n";
    TheGame::Instance()->quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }  
    }
}