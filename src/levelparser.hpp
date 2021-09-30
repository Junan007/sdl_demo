#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include "level.hpp"
#include "tinyxml/tinyxml.h"

class LevelParser
{
public:
    Level* parseLevel(const char* levelFile);
private:
    void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, std::vector<Tileset>* pTilesets);
    void parseTextures(TiXmlElement* pTextureRoot);
    void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers);

    int m_tileSize;
    int m_width;
    int m_height;
};

#endif