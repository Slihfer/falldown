#include "Game.h"

#include <chrono>
#include <stdlib.h>

#include <raylib.h>

#include "constants.h"
#include "macros.h"
#include "draw/Sprite.h"

Game::Game() : frameTime(0), runTime(0)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "falldown");
    SetTargetFPS(TARGET_FPS);
    //SetExitKey(0);

    srand(std::chrono::system_clock::now().time_since_epoch().count());
}

Game::~Game()
{

}

void Game::loadTextures()
{
    TextureInfo::load("tex_Player", FROM_SPRITES_FOLDER("player.png"));
    TextureInfo::load("tex_BaseTile", FROM_SPRITES_FOLDER("tile1.png"));
    TextureInfo::load("tex_BaseTileBG", FROM_SPRITES_FOLDER("bg_tile1.png"));
}

void Game::loadSprites()
{
    Sprite::load("spr_PlayerJump", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 16, 8, 8 });
    Sprite::load("spr_PlayerFall", TextureInfo::get("tex_Player").texture, Rectangle{ 8, 16, 8, 8 });

    Sprite::load("spr_BaseTile", TextureInfo::get("tex_BaseTile").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_BaseTileBG", TextureInfo::get("tex_BaseTileBG").texture, Rectangle{ 0, 0, 32, 32 });
}

void Game::loadAnimations()
{
    Animation::load("anim_PlayerIdle",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 0, 8, 8 } }, 5.0f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_PlayerWalk",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 16, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 } }, 0.1f });
}

void Game::update()
{
    level.update();
    view.update();
    player.update();
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    level.draw();
    player.draw();
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
        game.frameTime = std::min(MAX_FRAME_TIME, GetFrameTime());
        game.runTime += game.frameTime;

        game.update();
        game.draw();
    }

    CloseWindow();
}

float Game::delta()
{
    return instance().frameTime;
}

float Game::time()
{
    return instance().runTime;
}

View& Game::getView()
{
    return instance().view;
}

Level& Game::getLevel()
{
    return instance().level;
}

Player& Game::getPlayer()
{
    return instance().player;
}
