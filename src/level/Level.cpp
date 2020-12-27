#include "Level.h"

#include <iostream>

#include <raylib.h>

#include "core/constants.h"
#include "util/random.h"
#include "core/Game.h"
#include "draw/View.h"
#include "draw/draw.h"

Level::Level() : tiles(), y(-MAX_TILES_Y * TILE_DIMENSIONS), topRow(0), nextGroundRow(TILES_Y - 1)
{
    tiles.reserve(MAX_TILES_Y);

    for (int i = 0; i < MAX_TILES_Y; ++i)
    {
        std::vector<TileType> row;

        row.reserve(MAX_TILES_X);

        for (int j = 0; j < MAX_TILES_X; ++j)
            row.push_back(TileType::Empty);

        tiles.push_back(row);
    }

    generate();
}

std::vector<std::vector<TileType>>& Level::getTiles()
{
    return tiles;
}

std::vector<TileType>& Level::getTilesInRow(int row)
{
    return getTiles()[row];
}

bool Level::collides(float worldX, float worldY)
{
    return !(worldY < y || worldY >= y + MAX_TILES_Y * TILE_DIMENSIONS) &&
        ((worldX < 0) || (worldX >= MAX_TILES_X * TILE_DIMENSIONS) ||
        (getTile(worldToLevelCoords(worldX, worldY)) == TileType::Filled));
}

TileType& Level::getTile(int levelX, int levelY)
{
    return getTiles()[levelY][levelX];
}

TileType& Level::getTile(Vector2Int gridCoords)
{
    return getTile(gridCoords.x, gridCoords.y);
}

int Level::getTopRow()
{
    return topRow;
}

void Level::replaceTopRow()
{
    std::vector<TileType>& topTiles = getTilesInRow(topRow);

    if (topRow == nextGroundRow)
    {
        for (int i = 0; i < MAX_TILES_X; ++i)
            topTiles[i] = TileType::Filled;

        nextGroundRow = (topRow + GetRandomInt(GROUND_ROW_MIN_DISTANCE, GROUND_ROW_MAX_DISTANCE)) % MAX_TILES_Y;

        int empty = GetRandomInt(MAX_TILES_X - GROUND_ROW_MIN_TILES) + 1;
        int emptyStart = GetRandomInt(MAX_TILES_X - empty);

        for (int i = emptyStart; i < emptyStart + empty; ++i)
            topTiles[i] = TileType::Empty;

        if (GetRandomFloat() < BLOB_SPAWN_CHANCE)
            for (int i = 0; i < MAX_TILES_X; ++i)
                if (topTiles[i] == TileType::Filled)
                {
                    Game::spawnBlob(i * TILE_DIMENSIONS, y + (MAX_TILES_Y - 1) * TILE_DIMENSIONS);
                    break;
                }
    }
    else
    {
        for (int i = 0; i < MAX_TILES_X; ++i)
            topTiles[i] = TileType::Empty;
    }
}

void Level::generate()
{
    for (int i = 0; i < MAX_TILES_Y; ++i)
        advanceRow();
}

void Level::advanceRow()
{
    replaceTopRow();
    topRow = (topRow + 1) % MAX_TILES_Y;
    y += TILE_DIMENSIONS;
}

Vector2 Level::levelToWorldCoords(int levelX, int levelY)
{
    return { static_cast<float>(levelX * TILE_DIMENSIONS), y + ((MAX_TILES_Y + levelY - topRow) % MAX_TILES_Y) * TILE_DIMENSIONS };
}

Vector2Int Level::worldToLevelCoords(float worldX, float worldY)
{
    return { static_cast<int>(worldX / TILE_DIMENSIONS), (topRow + static_cast<int>(worldY - y) / TILE_DIMENSIONS) % MAX_TILES_Y };
}

void Level::update()
{
    while (Game::getView().getY() >= y + TILE_DIMENSIONS)
        advanceRow();
}

void Level::draw()
{
    for (int i = 0; i < MAX_TILES_X / 4; ++i)
        for (int j = 0; j < MAX_TILES_Y / 4 + 1; ++j)
            DrawSpriteParallax(Sprite::get("spr_BaseTileBG"), i * TILE_DIMENSIONS * 8, j * TILE_DIMENSIONS * 8 + floor(y / TILE_DIMENSIONS / 8) * TILE_DIMENSIONS * 8, 0.5f);

    for (int i = 0; i < MAX_TILES_X; ++i)
        for (int j = 0; j < MAX_TILES_Y; ++j)
            if (getTile(i, (topRow + j) % MAX_TILES_Y) == TileType::Filled)
                DrawSpriteWorld(Sprite::get("spr_BaseTile"), i * TILE_DIMENSIONS, j * TILE_DIMENSIONS + y);
}

void Level::print()
{
    for (int j = 0; j < MAX_TILES_Y; ++j)
    {
         for (int i = 0; i < MAX_TILES_X; ++i)
            std::cout << getTile(i, j) << " ";

        std::cout << "\n";
    }
}

bool Level::isAbove(float worldY)
{
    return worldY < y;
}
