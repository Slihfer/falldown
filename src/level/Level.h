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

public:
    Level();

private:
    TileType& getTile(int gridX, int gridY);
    TileType& getTile(Vector2Int gridCoords);
    std::vector<TileType>& getTilesInRow(int row);
    std::vector<std::vector<TileType>>& getTiles();
    int getTopRow();
    void replaceBottomRow();
    void generate();
    void advanceRow();

public:
    bool collides(float worldX, float worldY);
    bool collides(Rectangle collider);
    bool isAbove(float worldY);
    Rectangle getCollider(float worldX, float worldY);
    Vector2 handleCollision(Vector2& position, Rectangle collider, Vector2& velocity);
    Vector2 handleWallsCollision(Vector2& position, Rectangle collider, Vector2& velocity);
    Vector2 levelToWorldCoords(int levelX, int levelY);
    Vector2Int worldToLevelCoords(float worldX, float worldY);

    void update();
    void draw();
    void print();

public:
    static constexpr float BLOB_SPAWN_CHANCE = 0.25f;
};


