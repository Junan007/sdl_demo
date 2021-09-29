#include "levelparser.hpp"
#include "texturemanager.hpp"
#include "game.hpp"
#include "zlib.h"
#include "base64.hpp"
#include "tilelayer.hpp"

Level* LevelParser::parseLevel(const char* levelFile)
{
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level* pLevel = new Level();

    TiXmlElement* pRoot = levelDocument.RootElement();
    pRoot->Attribute("tilewidth", &m_tileSize);
    pRoot->Attribute("width", &m_width);
    pRoot->Attribute("height", &m_height);

    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("layer")) 
        {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), 
                                        pTilesetRoot->Attribute("name"), 
                                        TheGame::Instance()->getRenderer());
    
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");

    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, std::vector<Tileset>* pTilesets)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    std::vector<std::vector<int> > data;
    std::string decodedIDs;

    TiXmlElement* pDataNode;
    for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            pDataNode = e;
            break;
        }
    }

    for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        std::cout << "map data:" << t.c_str() << "\n";
        decodedIDs = base64_decode(t);
    }

    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());
    std::vector<int> layerRow(m_width);

    for (int j = 0;j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }

    pTileLayer->setTileIDs(data);
    pLayers->push_back(pTileLayer);
}
