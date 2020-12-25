#pragma once

#include <vector>

enum TileType { Empty, Filled, Count };

class TileGrid
{
private:
    std::vector<std::vector<TileType>> tiles;
    int topRow;
    int nextGroundRow;

    void replaceTopRow();

public:
    TileGrid();

    std::vector<std::vector<TileType>>& getTiles();
    std::vector<TileType>& getTilesInRow(int y);
    TileType& GetTile(int x, int y);

    int getTopRow();
    void generate();
    void advanceRow();
    void draw();
    void print();
};


