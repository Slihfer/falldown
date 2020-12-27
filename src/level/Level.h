#pragma once

#include <vector>

#include <raylib.h>

#include "util/vector.h"

enum TileType { Empty, Filled, Count };

class Level
{
private:
    std::vector<std::vector<TileType>> tiles;
    float y;
    int topRow;
    int nextGroundRow;

    TileType& getTile(int gridX, int gridY);
    TileType& getTile(Vector2Int gridCoords);
    int getTopRow();
    void replaceTopRow();
    void generate();
    void advanceRow();

public:
    Level();

    std::vector<std::vector<TileType>>& getTiles();
    std::vector<TileType>& getTilesInRow(int row);
    bool collides(float worldX, float worldY);
    bool isAbove(float worldY);

    Vector2 levelToWorldCoords(int levelX, int levelY);
    Vector2Int worldToLevelCoords(float worldX, float worldY);
    void update();
    void draw();
    void print();

public:
    static constexpr float BLOB_SPAWN_CHANCE = 0.5f;
};


