#include "Game.h"

#include <chrono>
#include <iostream>

#include <raylib.h>

#include "constants.h"
#include "macros.h"
#include "draw/TextureInfo.h"
#include "draw/Sprite.h"
#include "draw/Animation.h"

Game::Game() : frameTime(0), runTime(0), state(None), allowDestruction(false), destructionFlag(false)
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
    TextureInfo::load("tex_Blob", FROM_SPRITES_FOLDER("blob.png"));
    TextureInfo::load("tex_Powerup", FROM_SPRITES_FOLDER("powerup1.png"));

    TextureInfo::load("tex_BaseTile", FROM_SPRITES_FOLDER("tile1.png"));
    TextureInfo::load("tex_BaseTileBG", FROM_SPRITES_FOLDER("bg_tile1.png"));

    TextureInfo::load("tex_Button", FROM_SPRITES_FOLDER("button.png"));
}

void Game::loadSprites()
{
    Sprite::load("spr_PlayerLife", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_PlayerFastJump", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 16, 8, 8 });
    Sprite::load("spr_PlayerSlowJump", TextureInfo::get("tex_Player").texture, Rectangle{ 8, 16, 8, 8 });
    Sprite::load("spr_PlayerHover", TextureInfo::get("tex_Player").texture, Rectangle{ 16, 16, 8, 8 });
    Sprite::load("spr_PlayerFall", TextureInfo::get("tex_Player").texture, Rectangle{ 24, 16, 8, 8 });

    Sprite::load("spr_BaseTile", TextureInfo::get("tex_BaseTile").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_BaseTileBG", TextureInfo::get("tex_BaseTileBG").texture, Rectangle{ 0, 0, 32, 32 });

    Sprite::load("spr_ButtonTopLeft", TextureInfo::get("tex_Button").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_ButtonTop", TextureInfo::get("tex_Button").texture, Rectangle{ 8, 0, 8, 8 });
    Sprite::load("spr_ButtonLeft", TextureInfo::get("tex_Button").texture, Rectangle{ 0, 8, 8, 8 });
    Sprite::load("spr_ButtonCenter", TextureInfo::get("tex_Button").texture, Rectangle{ 8, 8, 8, 8 });
    Sprite::load("spr_ButtonBottomLeft", TextureInfo::get("tex_Button").texture, Rectangle{ 0, 16, 8, 8 });
    Sprite::load("spr_ButtonBottom", TextureInfo::get("tex_Button").texture, Rectangle{ 8, 16, 8, 8 });

    Sprite::load("spr_ButtonTopLeftSelected", TextureInfo::get("tex_Button").texture, Rectangle{ 16, 0, 8, 8 });
    Sprite::load("spr_ButtonTopSelected", TextureInfo::get("tex_Button").texture, Rectangle{ 24, 0, 8, 8 });
    Sprite::load("spr_ButtonLeftSelected", TextureInfo::get("tex_Button").texture, Rectangle{ 16, 8, 8, 8 });
    Sprite::load("spr_ButtonCenterSelected", TextureInfo::get("tex_Button").texture, Rectangle{ 24, 8, 8, 8 });
    Sprite::load("spr_ButtonBottomLeftSelected", TextureInfo::get("tex_Button").texture, Rectangle{ 16, 16, 8, 8 });
    Sprite::load("spr_ButtonBottomSelected", TextureInfo::get("tex_Button").texture, Rectangle{ 24, 16, 8, 8 });
}

void Game::loadAnimations()
{
    //Player
    Animation::load("anim_PlayerIdle",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 0, 8, 8 } }, 5.0f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_PlayerWalk",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 8, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 16, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 0, 8, 8, 8 } }, 0.1f });


    //Blob
    Animation::load("anim_BlobSpawn",
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 0, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 8, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 16, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 24, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_BlobIdle",
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 24, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 24, 8, 8, 8 } }, 0.1f });

    Animation::load("anim_BlobWalk",
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 0, 8, 8, 8 } }, 0.15f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 8, 8, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 16, 8, 8, 8 } }, 0.15f },
        Animation::Frame{ { TextureInfo::get("tex_Blob").texture, { 8, 8, 8, 8 } }, 0.15f });


    //Powerup
    Animation::load("anim_PowerupSpawn",
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 16, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 8, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 16, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 8, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 24, 8, 8, 8 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 8, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_PowerupIdle",
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 0, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 16, 0, 8, 8 } }, 0.3f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 0, 0, 8, 8 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 8, 0, 8, 8 } }, 0.3f });

    Animation::load("anim_PowerupDissipate",
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 0, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 8, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Powerup").texture, { 16, 16, 8, 8 } }, 0.05f });
}

void Game::initObjects()
{
    switchState(MainMenu);
}

void Game::update()
{
    allowDestruction = true;

    switch (state)
    {
    case MainMenu:
        if (IsKeyPressed(KEY_W))
        {
            buttons[selectedButton].selected = false;
            buttons[selectedButton = (selectedButton + buttons.size() - 1) % buttons.size()].selected = true;
        }
        else if (IsKeyPressed(KEY_S))
        {
            buttons[selectedButton].selected = false;
            buttons[selectedButton = (selectedButton + 1) % buttons.size()].selected = true;
        }

        for (Button& button : buttons)
            button.update();
        break;
    case Playing:
        level->update();
        view->update();
        player->update();
        updateDestructibles(blobs);
        updateDestructibles(powerups);
        break;
    }

    allowDestruction = false;
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (state)
    {
    case MainMenu:
        for (Button& button : buttons)
            button.draw();
        break;
    case Playing:
        level->draw();
        player->draw();
        for (Blob& blob : blobs) blob.draw();
        for (Powerup& powerup : powerups) powerup.draw();
        break;
    }

    EndDrawing();
}

void Game::run()
{
    Game& game = instance();

    game.loadTextures();
    game.loadSprites();
    game.loadAnimations();
    game.initObjects();

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

void Game::switchState(State newState)
{
    Game& game = instance();

    switch (newState)
    {
    case MainMenu:
        game.selectedButton = 0;
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.33f, TILES_X / 2, TILES_Y / 10 },
            "Play",
            5,
            [] { Game::switchState(Playing); },
            true
        );
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.67f, TILES_X / 2, TILES_Y / 10 },
            "Options",
            5,
            [] { Game::switchState(Playing); },
            false
        );
        break;
    case Playing:
        game.level = std::make_unique<Level>();
        game.player = std::make_unique<Player>();
        game.view = std::make_unique<View>();
        break;
    }

    game.state = newState;
}

void Game::flagDestruction()
{
    if (instance().allowDestruction)
        instance().destructionFlag = true;
}

Level& Game::getLevel()
{
    return *instance().level;
}

View& Game::getView()
{
    return *instance().view;
}

Player& Game::getPlayer()
{
    return *instance().player;
}