#include "stateparser.hpp"

bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs)
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
        }
    }

    TiXmlElement* pTextureRoot = 0;
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }

    parseTextures(pTextureRoot, pTextureIDs);

    TiXmlElement* pObjectRoot = 0;
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e!= NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }

    parseObjects(pStateRoot, pObjects);
    return true;
}

void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects)
{

}

void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{

}
