#include "stateparser.hpp"
#include "texturemanager.hpp"
#include "game.hpp"
#include "gameobjectfactory.hpp"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs)
{
    TiXmlDocument xmlDoc;
    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement();
    TiXmlElement* pStateRoot = 0;

    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == stateID) {
            pStateRoot = e;
            break;
        }
    }

    TiXmlElement* pTextureRoot = 0;
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
            break;
        }
    }

    parseTextures(pTextureRoot, pTextureIDs);

    TiXmlElement* pObjectRoot = 0;
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e!= NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
            break;
        }
    }

    parseObjects(pStateRoot, pObjects);
    return true;
}

void StateParser::parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbakID", &callbackID);
        e->Attribute("animSpeed", &animSpeed);
        textureID = e->Attribute("textureID");

        GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(x, y, width, height, textureID, callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}

void StateParser::parseTextures(TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs)
{
    for (TiXmlElement* e = pTextureRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute);
        TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
    }
}
