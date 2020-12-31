#include "Game.h"

#include <chrono>
#include <iostream>

#include <raylib.h>

#include "constants.h"
#include "macros.h"
#include "draw/TextureInfo.h"
#include "draw/Sprite.h"
#include "draw/Animation.h"

Game::Game() :
    shouldExit(false),
    frameTime(0),
    runTime(0),
    state(State::None),
    allowDestruction(false),
    destructionFlag(false),
    selectedButton(0)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "falldown");
    SetTargetFPS(TARGET_FPS);
    SetExitKey(0);

    srand(std::chrono::system_clock::now().time_since_epoch().count());
}

Game::~Game()
{

}

void Game::loadTextures()
{
//Objects
    TextureInfo::load("tex_Player", FROM_SPRITES_FOLDER("player.png"));
    TextureInfo::load("tex_Blob", FROM_SPRITES_FOLDER("blob.png"));
    TextureInfo::load("tex_GhostPowerup", FROM_SPRITES_FOLDER("ghost_powerup.png"));
    TextureInfo::load("tex_VoidPowerup", FROM_SPRITES_FOLDER("void_powerup.png"));
    TextureInfo::load("tex_VoidPowerupBG", FROM_SPRITES_FOLDER("void_powerupBG.png"));
    TextureInfo::load("tex_GhostAura", FROM_SPRITES_FOLDER("ghost_aura.png"));
    TextureInfo::load("tex_VoidAura", FROM_SPRITES_FOLDER("void_aura.png"));
    TextureInfo::load("tex_VoidAuraBG", FROM_SPRITES_FOLDER("void_auraBG.png"));
    TextureInfo::load("tex_Spikes", FROM_SPRITES_FOLDER("spikes.png"));
    TextureInfo::load("tex_Turret", FROM_SPRITES_FOLDER("laser_turret.png"));


//Level
    TextureInfo::load("tex_BaseTile", FROM_SPRITES_FOLDER("tile1.png"));
    TextureInfo::load("tex_BaseTileBG", FROM_SPRITES_FOLDER("bg_tile1.png"));

    
//UI
    TextureInfo::load("tex_Button", FROM_SPRITES_FOLDER("button.png"));
}

void Game::loadSprites()
{
//Player
    Sprite::load("spr_PlayerLife", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_PlayerFastJump", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 16, 8, 8 });
    Sprite::load("spr_PlayerSlowJump", TextureInfo::get("tex_Player").texture, Rectangle{ 8, 16, 8, 8 });
    Sprite::load("spr_PlayerHover", TextureInfo::get("tex_Player").texture, Rectangle{ 16, 16, 8, 8 });
    Sprite::load("spr_PlayerFall", TextureInfo::get("tex_Player").texture, Rectangle{ 24, 16, 8, 8 });
    Sprite::load("spr_PlayerHurt", TextureInfo::get("tex_Player").texture, Rectangle{ 16, 0, 8, 8 });

    Sprite::load("spr_GhostAura", TextureInfo::get("tex_GhostAura").texture, Rectangle{ 0, 0, 16, 16 });
    Sprite::load("spr_VoidAura", TextureInfo::get("tex_VoidAura").texture, Rectangle{ 0, 0, 40, 40 });


//Spikes
    Sprite::load("spr_SpikesIdle", TextureInfo::get("tex_Spikes").texture, Rectangle{ 0, 0, 8, 16 });
    Sprite::load("spr_SpikesOut", TextureInfo::get("tex_Spikes").texture, Rectangle{ 24, 0, 8, 16 });


//Turret
    Sprite::load("spr_TurretIdle", TextureInfo::get("tex_Turret").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_TurretCharge", TextureInfo::get("tex_Turret").texture, Rectangle{ 8, 0, 8, 8 });
    Sprite::load("spr_TurretShoot", TextureInfo::get("tex_Turret").texture, Rectangle{ 16, 0, 8, 8 });


//Level
    Sprite::load("spr_BaseTile", TextureInfo::get("tex_BaseTile").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_BaseTileBG", TextureInfo::get("tex_BaseTileBG").texture, Rectangle{ 0, 0, 32, 32 });


//Button
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

    Animation::load("anim_VoidAuraSpawn",
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 80, 0, 40, 40 } }, 0.15f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 40, 0, 40, 40 } }, 0.15f });

    Animation::load("anim_VoidAuraDissipate",
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 40, 0, 40, 40 } }, 0.15f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 80, 0, 40, 40 } }, 0.15f });

    Animation::load("anim_VoidAuraBG",
        Animation::Frame{ { TextureInfo::get("tex_VoidAuraBG").texture, { 0, 0, 40, 40 }}, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAuraBG").texture, { 40, 0, 40, 40 }}, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAuraBG").texture, { 80, 0, 40, 40 }}, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAuraBG").texture, { 120, 0, 40, 40 }}, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAuraBG").texture, { 160, 0, 40, 40 }}, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAuraBG").texture, { 200, 0, 40, 40 }}, 0.1f });

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


//Ghost Powerup
    Animation::load("anim_GhostPowerupSpawn",
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 16, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 8, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 16, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 8, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 24, 8, 8, 8 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 8, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_GhostPowerupIdle",
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 0, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 16, 0, 8, 8 } }, 0.3f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 0, 0, 8, 8 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 8, 0, 8, 8 } }, 0.3f });

    Animation::load("anim_GhostPowerupDissipate",
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 0, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 8, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_GhostPowerup").texture, { 16, 16, 8, 8 } }, 0.05f });


//Void Powerup
    Animation::load("anim_VoidPowerupSpawn",
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 0, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 8, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 16, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 24, 8, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 0, 16, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 8, 16, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 16, 16, 8, 8 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 24, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_VoidPowerupIdle",
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 0, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 8, 0, 8, 8 } }, 0.3f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 0, 0, 8, 8 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 16, 8, 8, 8 } }, 0.3f });

    Animation::load("anim_VoidPowerupDissipate",
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 8, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerup").texture, { 24, 8, 8, 8 } }, 0.1f });

    Animation::load("anim_VoidPowerupSpawnBG",
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerupBG").texture, { 0, 0, 8, 8 } }, 0.4f });

    Animation::load("anim_VoidPowerupIdleBG",
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerupBG").texture, { 0, 0, 8, 8 } }, 0.1f });

    Animation::load("anim_VoidPowerupDissipateBG",
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerupBG").texture, { 0, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_VoidPowerupBG").texture, { 8, 0, 8, 8 } }, 0.1f });


//Spikes
    Animation::load("anim_SpikesPoke",
        Animation::Frame{ { TextureInfo::get("tex_Spikes").texture, { 8, 0, 8, 16 } }, 0.025f },
        Animation::Frame{ { TextureInfo::get("tex_Spikes").texture, { 16, 0, 8, 16 } }, 0.025f });

    Animation::load("anim_SpikesRetract",
        Animation::Frame{ { TextureInfo::get("tex_Spikes").texture, { 16, 0, 8, 16 } }, 0.2f },
        Animation::Frame{ { TextureInfo::get("tex_Spikes").texture, { 8, 0, 8, 16 } }, 0.2f });


//Turret
    Animation::load("anim_TurretRetract",
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 24, 0, 8, 8 } }, 0.2f });

//Turret Beam
    Animation::load("anim_TurretBeamCharge",
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 0, 8, 8, 8 } }, 0.25f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 8, 8, 8, 8 } }, 0.25f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 16, 8, 8, 8 } }, 0.25f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 24, 8, 8, 8 } }, 0.25f });

    Animation::load("anim_TurretBeamStart",
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 0, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 8, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 16, 16, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 24, 16, 8, 8 } }, 0.05f });

    Animation::load("anim_TurretBeamCenter",
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 0, 24, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 8, 24, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 16, 24, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 24, 24, 8, 8 } }, 0.05f });

    Animation::load("anim_TurretBeamEnd",
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 0, 32, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 8, 32, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 16, 32, 8, 8 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_Turret").texture, { 24, 32, 8, 8 } }, 0.05f });
}

void Game::initObjects()
{
    setState(State::MainMenu);
}

void Game::update()
{
    allowDestruction = true;

    switch (state)
    {
    case State::MainMenu:
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
    case State::Playing:
        if (IsKeyPressed(KEY_ESCAPE))
        {
            setState(State::MainMenu);
            break;
        }

        level->update();
        view->update();
        player->update();
        updateDestructibles(blobs);
        updateDestructibles(ghostPowerups);
        updateDestructibles(voidPowerups);
        updateDestructibles(spikes);
        updateDestructibles(turrets);

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
    case State::MainMenu:
        for (Button& button : buttons) button.draw();
        break;
    case State::Playing:
        level->draw();
        for (Blob& blob : blobs) blob.draw();
        for (GhostPowerup& ghostPowerup : ghostPowerups) ghostPowerup.draw();
        for (VoidPowerup& voidPowerup : voidPowerups) voidPowerup.draw();
        for (Spikes& spike : spikes) spike.draw();
        for (Turret& turret : turrets) turret.draw();
        player->draw();
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

    while (!(WindowShouldClose() || game.shouldExit))
    {
        game.frameTime = std::min(MAX_FRAME_TIME, GetFrameTime());
        game.runTime += game.frameTime;

        game.update();
        game.draw();
    }

    CloseWindow();
}

void Game::exit()
{
    instance().shouldExit = true;
}

float Game::delta()
{
    return instance().frameTime;
}

float Game::time()
{
    return instance().runTime;
}

void Game::setState(State newState)
{
    Game& game = instance();

    switch (game.state)
    {
    case State::MainMenu:
        game.buttons.clear();
        break;
    case State::Playing:
        game.level.release();
        game.view.release();
        game.player.release();
        game.blobs.clear();
        game.ghostPowerups.clear();
        game.spikes.clear();
        break;
    }

    switch (newState)
    {
    case State::MainMenu:
        game.selectedButton = 0;
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.33f, TILES_X / 2, TILES_Y / 10 },
            "Play",
            5,
            [] { Game::setState(State::Playing); },
            true
        );
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.67f, TILES_X / 2, TILES_Y / 10 },
            "Exit",
            5,
            [] { Game::exit(); },
            false
        );
        break;
    case State::Playing:
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