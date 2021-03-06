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
    TileType& getTile(int levelX, int levelY);
    TileType& getTile(Vector2Int levelCoords);
    std::vector<TileType>& getTilesInRow(int row);
    std::vector<std::vector<TileType>>& getTiles();
    int getTopRow();
    void replaceBottomRow();
    void generate();
    void advanceRow();
    void handleVoidAuraCollisions();

public:
    bool collides(float worldX, float worldY);
    bool collides(Rectangle collider);
    bool outOfBounds(float worldX, float worldY);
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
    static constexpr float SPIKES_SPAWN_CHANCE = 0.5f;
    static constexpr float TURRET_SPAWN_CHANCE = 0.1f;
    static constexpr float POWERUP_SPAWN_CHANCE = 0.25f;
    static constexpr float VOID_SPAWN_CHANCE = 0.25f;
};


