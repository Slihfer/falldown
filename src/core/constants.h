#pragma once

//TODO move stuff

constexpr int TILE_DIMENSIONS = 8;
constexpr int HALF_TILE_DIMENSIONS = TILE_DIMENSIONS / 2;
constexpr int ZOOM = 5;
constexpr int TILES_X = 16;
constexpr int TILES_Y = 24;
constexpr int MAX_TILES_X = TILES_X;
constexpr int MAX_TILES_Y = TILES_Y + 3;
constexpr int GROUND_ROW_MIN_DISTANCE = 4;
constexpr int GROUND_ROW_MAX_DISTANCE = 9;
constexpr int GROUND_ROW_MIN_TILES = MAX_TILES_X / 2;
constexpr int LEVEL_WIDTH = TILE_DIMENSIONS * TILES_X;
constexpr int LEVEL_HEIGHT = TILE_DIMENSIONS * TILES_Y;
constexpr int WINDOW_WIDTH = LEVEL_WIDTH * ZOOM;
constexpr int WINDOW_HEIGHT = LEVEL_HEIGHT * ZOOM;
constexpr int VIEW_MAX_PLAYER_DISTANCE = LEVEL_HEIGHT * 2 / 3;

constexpr int TARGET_FPS = 60;
constexpr float MAX_FRAME_TIME = 0.1f;