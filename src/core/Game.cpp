#include "Game.h"

#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "constants.h"

Game::Game()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "falldown");
    SetTargetFPS(TARGET_FPS);
    //SetExitKey(0);

    srand(time(0));
    
    level.generate();
}

Game::~Game()
{
}

void Game::update()
{
    level.advanceRow();
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(WHITE);
    level.draw();
    EndDrawing();
}

void Game::run()
{
    Game& game = instance();

    while (!WindowShouldClose())
    {
        game.update();
        game.draw();
    }

    CloseWindow();
}
