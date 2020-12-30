#include "Level.h"

#include <iostream>
#include <numeric>
#include <limits>

#include <raylib.h>

#include "core/constants.h"
#include "util/random.h"
#include "core/Game.h"
#include "draw/View.h"
#include "draw/draw.h"
#include "util/collision.h"
#include "util/rectangle.h"

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

TileType& Level::getTile(int levelX, int levelY)
{
    return getTiles()[levelY][levelX];
}

TileType& Level::getTile(Vector2Int gridCoords)
{
    return getTile(gridCoords.x, gridCoords.y);
}

std::vector<TileType>& Level::getTilesInRow(int row)
{
    return getTiles()[row];
}

std::vector<std::vector<TileType>>& Level::getTiles()
{
    return tiles;
}

int Level::getTopRow()
{
    return topRow;
}

void Level::replaceBottomRow()
{
    int bottomRow = (topRow + MAX_TILES_Y - 1) % MAX_TILES_Y;
    std::vector<TileType>& bottomTiles = getTilesInRow(bottomRow);

    if (bottomRow == nextGroundRow)
    {
        for (int i = 0; i < MAX_TILES_X; ++i)
            bottomTiles[i] = TileType::Filled;

        nextGroundRow = (bottomRow + GetRandomInt(GROUND_ROW_MIN_DISTANCE, GROUND_ROW_MAX_DISTANCE)) % MAX_TILES_Y;

        int empty = GetRandomInt(MAX_TILES_X - GROUND_ROW_MIN_TILES) + 1;
        int emptyStart = GetRandomInt(MAX_TILES_X - empty);

        for (int i = emptyStart; i < emptyStart + empty; ++i)
            bottomTiles[i] = TileType::Empty;

        if (float r = GetRandomFloat(); r < SPIKES_SPAWN_CHANCE)
        {
            r = floor(r / SPIKES_SPAWN_CHANCE * (MAX_TILES_X - empty));

            for (int i = 0; i < MAX_TILES_X - empty; ++i)
                if (r == i)
                {
                    Game::spawnSpikes(levelToWorldCoords(i >= emptyStart ? i + empty : i, bottomRow) - Vector2{ 0, TILE_DIMENSIONS });
                    break;
                }
        }
        else if (float r = GetRandomFloat(); r < BLOB_SPAWN_CHANCE)
        {
            r = floor(r / BLOB_SPAWN_CHANCE * (MAX_TILES_X - empty));

            for (int i = 0; i < MAX_TILES_X - empty; ++i)
                if (r == i)
                {
                    Game::spawnBlob(levelToWorldCoords(i >= emptyStart ? i + empty : i, bottomRow) - Vector2{ 0, TILE_DIMENSIONS });
                    break;
                }
        }

    endBlobSpawn:
        if (empty == 1 && GetRandomFloat() < POWERUP_SPAWN_CHANCE)
            Game::spawnPowerup(levelToWorldCoords(emptyStart, bottomRow));
    }
    else
    {
        for (int i = 0; i < MAX_TILES_X; ++i)
            bottomTiles[i] = TileType::Empty;

        if (GetRandomFloat() < TURRET_SPAWN_CHANCE)
        {
            if (bool left = GetRandomBool(); left)
                Game::spawnTurret(levelToWorldCoords(0, bottomRow), false);
            else
                Game::spawnTurret(levelToWorldCoords(MAX_TILES_X - 1, bottomRow), true);
        }
    }
}

void Level::generate()
{
    for (int i = 0; i < MAX_TILES_Y; ++i)
        advanceRow();
}

void Level::advanceRow()
{
    y += TILE_DIMENSIONS;
    topRow = (topRow + 1) % MAX_TILES_Y;
    replaceBottomRow();
}

bool Level::collides(float worldX, float worldY)
{
    return !(worldY < y || worldY >= y + MAX_TILES_Y * TILE_DIMENSIONS) &&
        ((worldX < 0) || (worldX >= MAX_TILES_X * TILE_DIMENSIONS) ||
        (getTile(worldToLevelCoords(worldX, worldY)) == TileType::Filled));
}

bool Level::collides(Rectangle collider)
{
    std::vector<Rectangle> touching;

    for (int x = floor(collider.x / TILE_DIMENSIONS) * TILE_DIMENSIONS; x - collider.x < collider.width; x += TILE_DIMENSIONS)
        for (int y = floor(collider.y / TILE_DIMENSIONS) * TILE_DIMENSIONS; y - collider.y < collider.height; y += TILE_DIMENSIONS)
            if (collides(x, y))
                return true;

    return false;
}

bool Level::isAbove(float worldY)
{
    return worldY < y;
}

Rectangle Level::getCollider(float worldX, float worldY)
{
    return {
        floor(worldX / TILE_DIMENSIONS) * TILE_DIMENSIONS,
        floor(worldY / TILE_DIMENSIONS) * TILE_DIMENSIONS,
        TILE_DIMENSIONS,
        TILE_DIMENSIONS
    };
}

Vector2 Level::handleCollision(Vector2& position, Rectangle collider, Vector2& velocity)
{
    Vector2 result{};
    Rectangle ac = AssembleCollider(position, collider);
    Rectangle pc = MoveRectangle(ac, -velocity * Game::delta());

    while (true)
    {
        std::vector<Rectangle> touching;

        for (int x = floor(ac.x / TILE_DIMENSIONS) * TILE_DIMENSIONS; x - ac.x < ac.width; x += TILE_DIMENSIONS)
            for (int y = floor(ac.y / TILE_DIMENSIONS) * TILE_DIMENSIONS; y - ac.y < ac.height; y += TILE_DIMENSIONS)
                if (collides(x, y))
                    touching.push_back(getCollider(x, y));

        if (touching.empty())
            return result;

        Vector2 acc = GetRectangleCenter(ac);
        Vector2 unstuckResult =
            GetFixedMobileUnstuckVector(
                *std::min_element(
                    touching.begin(),
                    touching.end(),
                    [acc](Rectangle r1, Rectangle r2)
                    { return distance(GetRectangleCenter(r1), acc) < distance(GetRectangleCenter(r2), acc); }),
                ac,
                pc);

        result += unstuckResult;
        position += unstuckResult;

        if (unstuckResult.x)
            position.x = round(position.x);

        if (unstuckResult.y)
            position.y = round(position.y);

        if (unstuckResult.x * velocity.x < 0)
            velocity.x = 0;

        if (unstuckResult.y * velocity.y < 0)
            velocity.y = 0;

        ac = AssembleCollider(position, collider);
    }
}

Vector2 Level::handleWallsCollision(Vector2& position, Rectangle collider, Vector2& velocity)
{
    Rectangle ac = AssembleCollider(position, collider);

    if (ac.x < 0)
    {
        position.x = -collider.x;
        velocity.x = 0;
        return { -ac.x, 0 };
    }
    else if (float acr = GetRectangleRight(ac); acr > LEVEL_WIDTH)
    {
        position.x = LEVEL_WIDTH - GetRectangleRight(collider);
        velocity.x = 0;
        return { LEVEL_WIDTH - acr };
    }

    return {};
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
                if (Game::getPlayer().collisionEnabled)
                    DrawSpriteWorld(Sprite::get("spr_BaseTile"), i * TILE_DIMENSIONS, j * TILE_DIMENSIONS + y);
                else
                    DrawSpriteWorld(Sprite::get("spr_BaseTilePowerup"), i * TILE_DIMENSIONS, j * TILE_DIMENSIONS + y, false, true);
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
