#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <string>
#include <map>
#include "gameobject.hpp"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    static GameObjectFactory* Instance()
    {
        if (s_pGameObjectFact == NULL)
        {
            s_pGameObjectFact = new GameObjectFactory();
            return s_pGameObjectFact;
        }
        return s_pGameObjectFact;
    }

    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        if (it != m_creators.end())
        {
            delete pCreator;
            return false;
        }

        m_creators[typeID] = pCreator;
        return true;
    }

    GameObject* create(std::string typeID)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        if (it == m_creators.end())
        {
            std::cout << "could not find type: " << typeID <<"\n";
            return NULL;
        }

        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }

private:
    static GameObjectFactory* s_pGameObjectFact;
    std::map<std::string, BaseCreator*> m_creators;
};

#endif