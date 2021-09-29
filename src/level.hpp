#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "layer.hpp"

#include <string>

struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:
    ~Level() {}

    void update();
    void render();

    std::vector<Tileset>* getTilesets()
    {
        return &m_tilesets;
    }

    std::vector<Layer*>* getLayers()
    {
        return &m_layers;
    }
private:
    friend class LevelParser;   // 仅LevelParser类能创建Level对象。
    Level() {};
private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};

#endif