#include "Game.h"

#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "constants.h"
#include "macros.h"
#include "draw/Sprite.h"

Game::Game()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "falldown");
    SetTargetFPS(TARGET_FPS);
    //SetExitKey(0);

    renderTarget = LoadRenderTexture(LEVEL_WIDTH, LEVEL_HEIGHT);

    srand(time(0));
}

Game::~Game()
{
    UnloadRenderTexture(renderTarget);
}

void Game::loadTextures()
{
    TextureInfo::load("tex_BaseTile", FROM_SPRITES_FOLDER("tile1.png"));
    TextureInfo::load("tex_Player", FROM_SPRITES_FOLDER("player.png"));
}

void Game::loadSprites()
{
    Sprite::load("spr_BaseTile", TextureInfo::get("tex_BaseTile").texture, Rectangle{ 0, 0, 8, 8 }, false);
    Sprite::load("spr_Player", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 0, 8, 8 }, false);
}

void Game::loadAnimations()
{
}

void Game::update(float t)
{
    level.update(t);
    view.update(t);
    player.update(t);
}

void Game::draw()
{
    BeginDrawing();
        BeginTextureMode(renderTarget);
            ClearBackground(BLACK);
            level.draw();
            player.draw();
        EndTextureMode();

        DrawTexturePro(
            renderTarget.texture,
            { 0, 0, LEVEL_WIDTH, -LEVEL_HEIGHT },
            { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT },
            {},
            0,
            WHITE);
    EndDrawing();
}

void Game::run()
{
    Game& game = instance();

    game.loadTextures();
    game.loadSprites();
    game.loadAnimations();

    while (!WindowShouldClose())
    {
        float t = GetFrameTime();

        game.update(t);
        game.draw();
    }

    CloseWindow();
}

View& Game::getView()
{
    return instance().view;
}

Level& Game::getLevel()
{
    return instance().level;
}
