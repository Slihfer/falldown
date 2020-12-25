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
    Sprite::load("spr_PlayerIdle_R", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 0, 8, 8 }, false);
    Sprite::load("spr_PlayerIdle_L", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 0, 8, 8 }, true);
    Sprite::load("spr_PlayerJump_R", TextureInfo::get("tex_Player").texture, Rectangle{ 8, 8, 8, 8 }, false);
    Sprite::load("spr_PlayerJump_L", TextureInfo::get("tex_Player").texture, Rectangle{ 8, 8, 8, 8 }, true);
    Sprite::load("spr_PlayerFall_R", TextureInfo::get("tex_Player").texture, Rectangle{ 16, 0, 8, 8 }, false);
    Sprite::load("spr_PlayerFall_L", TextureInfo::get("tex_Player").texture, Rectangle{ 16, 0, 8, 8 }, true);
}

void Game::loadAnimations()
{
    Animation::load("anim_PlayerIdle_R",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 0, 8, 8 }, false }, 5.0f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 0, 8, 8 }, false }, 0.1f });
    Animation::load("anim_PlayerIdle_L",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 0, 8, 8 }, true }, 5.0f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 0, 8, 8 }, true }, 0.1f });

    Animation::load("anim_PlayerWalk_R",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 8, 8, 8 }, false }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 }, false }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 16, 8, 8, 8 }, false }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 }, false }, 0.1f });
    Animation::load("anim_PlayerWalk_L",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 }, true }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 8, 8, 8 }, true }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 }, true }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 16, 8, 8, 8 }, true }, 0.1f });
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
