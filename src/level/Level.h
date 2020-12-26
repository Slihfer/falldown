#pragma once

#include <vector>

#include <raylib.h>

enum TileType { Empty, Filled, Count };

class Level
{
private:
    std::vector<std::vector<TileType>> tiles;
    float y;
    int topRow;
    int nextGroundRow;

    void replaceTopRow();
    TileType& getTile(int gridX, int gridY);

public:
    Level();

    std::vector<std::vector<TileType>>& getTiles();
    std::vector<TileType>& getTilesInRow(int row);
    bool collides(float worldX, float worldY);

    int getTopRow();
    void generate();
    void advanceRow();
    void update();
    void draw();
    void print();

public:
    static constexpr float BLOB_SPAWN_CHANCE = 0.5f;
};


