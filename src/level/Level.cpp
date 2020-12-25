#include "Level.h"

#include <iostream>

#include <raylib.h>

#include "core/constants.h"
#include "util/random.h"

TileGrid::TileGrid() : tiles(), topRow(0), nextGroundRow(MAX_TILES_Y - 1)
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
}

std::vector<std::vector<TileType>>& TileGrid::getTiles()
{
    return tiles;
}

std::vector<TileType>& TileGrid::getTilesInRow(int y)
{
    return getTiles()[y];
}

TileType& TileGrid::GetTile(int x, int y)
{
    return getTiles()[y][x];
}

int TileGrid::getTopRow()
{
    return topRow;
}

void TileGrid::replaceTopRow()
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
    }
    else
    {
        for (int i = 0; i < MAX_TILES_X; ++i)
            topTiles[i] = TileType::Empty;
    }
}

void TileGrid::generate()
{
    for (int i = 0; i < MAX_TILES_Y; ++i)
        advanceRow();
}

void TileGrid::advanceRow()
{
    replaceTopRow();
    topRow = (topRow + 1) % MAX_TILES_Y;
}

void TileGrid::draw()
{
    for (int i = 0; i < MAX_TILES_X; ++i)
        for (int j = 0; j < MAX_TILES_Y; ++j)
            DrawRectangle(
                i * TILE_DIMENSIONS * ZOOM,
                j * TILE_DIMENSIONS * ZOOM,
                TILE_DIMENSIONS * ZOOM,
                TILE_DIMENSIONS * ZOOM,
                GetTile(i, (topRow + j) % MAX_TILES_Y) == TileType::Filled ? WHITE : BLACK);
}

void TileGrid::print()
{
    for (int j = 0; j < MAX_TILES_Y; ++j)
    {
         for (int i = 0; i < MAX_TILES_X; ++i)
            std::cout << GetTile(i, j) << " ";

        std::cout << "\n";
    }
}