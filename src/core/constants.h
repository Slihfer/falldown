#pragma once

constexpr int TILE_DIMENSIONS = 8;
constexpr int ZOOM = 4;
constexpr int TILES_X = 12;
constexpr int TILES_Y = 24;
constexpr int MAX_TILES_X = TILES_X;
constexpr int MAX_TILES_Y = TILES_Y + 1;
constexpr int GROUND_ROW_MIN_DISTANCE = 4;
constexpr int GROUND_ROW_MAX_DISTANCE = 9;
constexpr int GROUND_ROW_MIN_TILES = MAX_TILES_X / 2;
constexpr int WINDOW_WIDTH = TILE_DIMENSIONS * ZOOM * TILES_X;
constexpr int WINDOW_HEIGHT = TILE_DIMENSIONS * ZOOM * TILES_Y;
constexpr int TARGET_FPS = 60;