#ifndef TILELAYER_H
#define TILELAYER_H

#include "vector"
#include "layer.hpp"
#include "vector2d.hpp"
#include "level.hpp"

class TileLayer : public Layer
{
public:
    TileLayer(int tileSize, std::vector<Tileset> &tilesets);

    virtual void update();
    virtual void render();

    void setTileIDs(const std::vector<std::vector<int> > &data)
    {
        m_tileIDs = data;
    }

    void setTileSize(int tileSize)
    {
        m_tileSize = tileSize;
    }

    Tileset getTilesetByID(int tileID);

private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    Vector2D m_position;
    Vector2D m_velocity;

    std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<int> > m_tileIDs;
};

#endif