#include "Game.h"

#include <chrono>
#include <iostream>

#include <raylib.h>

#include "constants.h"
#include "input.h"
#include "macros.h"
#include "draw/TextureInfo.h"
#include "draw/Sprite.h"
#include "draw/Animation.h"
#include "draw/draw.h"
#include "sound/SoundEffect.h"
#include "screens/Credits.h"
#include "screens/GameOver.h"
#include "screens/MenuBackground.h"

Game::Game() :
    StateObject(State::None, 0.0f, true),
    shouldExit(false),
    frameTime(TARGET_FRAME_TIME),
    runTime(0),
    unpausedRunTime(0),
    allowDestruction(false),
    destructionFlag(false),
    paused(false),
    unpauseTime(COUNTDOWN, std::numeric_limits<float>::infinity(), true),
    queuedState(State::None),
    gameOver(false),
    fullMouseControl(false),
    selectedButton(0),
    objects(),
    mousePosition{ -1.0f, -1.0f },
    lastMousePosition{ -1.0f, -1.0f },
    lastControllerLeftStickAxis{},
    spawnTime(std::numeric_limits<float>::infinity()),
    deathTime(std::numeric_limits<float>::infinity())
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "falldown");
    SetTargetFPS(TARGET_FPS);
    SetWindowTitle(GAME_TITLE);
    SetExitKey(0);

    InitAudioDevice();

    srand(std::chrono::system_clock::now().time_since_epoch().count());

    SetMousePosition(-1, -1);
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
    TextureInfo::load("tex_UI", FROM_SPRITES_FOLDER("ui.png"));
}

void Game::loadSprites()
{
//Player
    Sprite::load("spr_PlayerLife", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_PlayerFastJump", TextureInfo::get("tex_Player").texture, Rectangle{ 0, 16, 8, 8 });
    Sprite::load("spr_PlayerSlowJump", TextureInfo::get("tex_Player").texture, Rectangle{ 8, 16, 8, 8 });
    Sprite::load("spr_PlayerHover", TextureInfo::get("tex_Player").texture, Rectangle{ 16, 16, 8, 8 });
    Sprite::load("spr_PlayerFall", TextureInfo::get("tex_Player").texture, Rectangle{ 24, 16, 8, 8 });

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
    Sprite::load("spr_ButtonTopLeft", TextureInfo::get("tex_UI").texture, Rectangle{ 0, 0, 8, 8 });
    Sprite::load("spr_ButtonTop", TextureInfo::get("tex_UI").texture, Rectangle{ 8, 0, 8, 8 });
    Sprite::load("spr_ButtonLeft", TextureInfo::get("tex_UI").texture, Rectangle{ 0, 8, 8, 8 });
    Sprite::load("spr_ButtonCenter", TextureInfo::get("tex_UI").texture, Rectangle{ 8, 8, 8, 8 });
    Sprite::load("spr_ButtonBottomLeft", TextureInfo::get("tex_UI").texture, Rectangle{ 0, 16, 8, 8 });
    Sprite::load("spr_ButtonBottom", TextureInfo::get("tex_UI").texture, Rectangle{ 8, 16, 8, 8 });

    Sprite::load("spr_ButtonTopLeftSelected", TextureInfo::get("tex_UI").texture, Rectangle{ 16, 0, 8, 8 });
    Sprite::load("spr_ButtonTopSelected", TextureInfo::get("tex_UI").texture, Rectangle{ 24, 0, 8, 8 });
    Sprite::load("spr_ButtonLeftSelected", TextureInfo::get("tex_UI").texture, Rectangle{ 16, 8, 8, 8 });
    Sprite::load("spr_ButtonCenterSelected", TextureInfo::get("tex_UI").texture, Rectangle{ 24, 8, 8, 8 });
    Sprite::load("spr_ButtonBottomLeftSelected", TextureInfo::get("tex_UI").texture, Rectangle{ 16, 16, 8, 8 });
    Sprite::load("spr_ButtonBottomSelected", TextureInfo::get("tex_UI").texture, Rectangle{ 24, 16, 8, 8 });

    Sprite::load("spr_UIBoxTopLeft", TextureInfo::get("tex_UI").texture, Rectangle{ 32, 0, 8, 8 });
    Sprite::load("spr_UIBoxTop", TextureInfo::get("tex_UI").texture, Rectangle{ 40, 0, 8, 8 });
    Sprite::load("spr_UIBoxLeft", TextureInfo::get("tex_UI").texture, Rectangle{ 32, 8, 8, 8 });
    Sprite::load("spr_UIBoxCenter", TextureInfo::get("tex_UI").texture, Rectangle{ 40, 8, 8, 8 });
    Sprite::load("spr_UIBoxBottomLeft", TextureInfo::get("tex_UI").texture, Rectangle{ 32, 16, 8, 8 });
    Sprite::load("spr_UIBoxBottom", TextureInfo::get("tex_UI").texture, Rectangle{ 40, 16, 8, 8 });
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

    Animation::load("anim_PlayerHurt",
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 16, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 24, 0, 8, 8 } }, 0.1f },
        Animation::Frame{ { TextureInfo::get("tex_Player").texture, { 16, 0, 8, 8 } }, 0.0f });

    Animation::load("anim_VoidAuraSpawn",
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 80, 0, 40, 40 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 40, 0, 40, 40 } }, 0.05f });

    Animation::load("anim_VoidAuraDissipate",
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 40, 0, 40, 40 } }, 0.05f },
        Animation::Frame{ { TextureInfo::get("tex_VoidAura").texture, { 80, 0, 40, 40 } }, 0.05f });

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

    Animation::load("anim_BlobTurn",
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

void Game::loadSoundEffects()
{
    SoundEffect::load("music_Main", FROM_MUSIC_FOLDER("bg_music.wav"), 1.0f);

    SoundEffect::load("sfx_ButtonCycle", FROM_SFX_FOLDER("button_cycle.wav"), 0.6f);
    SoundEffect::load("sfx_Accept", FROM_SFX_FOLDER("accept.wav"), 0.8f);
    SoundEffect::load("sfx_BlobJump", FROM_SFX_FOLDER("blob_jump.wav"), 0.2f);
    SoundEffect::load("sfx_Jump", FROM_SFX_FOLDER("jump.wav"), 0.5f);
    SoundEffect::load("sfx_Hurt", FROM_SFX_FOLDER("hurt.wav"), 0.65f);
    SoundEffect::load("sfx_Die", FROM_SFX_FOLDER("die.wav"), 0.65f);
    SoundEffect::load("sfx_Land", FROM_SFX_FOLDER("land.wav"), 0.25f);
    SoundEffect::load("sfx_Spikes", FROM_SFX_FOLDER("spikes.wav"), 0.35f);
    SoundEffect::load("sfx_LaserCharge", FROM_SFX_FOLDER("laser0.wav"), 0.2f);
    SoundEffect::load("sfx_LaserShoot", FROM_SFX_FOLDER("laser1.wav"), 0.2f);
    SoundEffect::load("sfx_VoidPickup", FROM_SFX_FOLDER("void_pickup.wav"), 1.5f);
    SoundEffect::load("sfx_VoidAura", FROM_SFX_FOLDER("void_aura.wav"), 1.5f);
    SoundEffect::load("sfx_GhostPickup", FROM_SFX_FOLDER("ghost_pickup.wav"), 0.5f);
}

void Game::initLogic()
{
    setState(State::MainMenu);
}

void Game::update()
{
    if (queuedState != State::None) setState(queuedState);
    if (paused && unpauseTime.isExpired()) unpause();
    if (!paused && pauseQueued) pause();

    allowDestruction = true;

    if (IsInputStarted<InputAction::Up>())
        cycleSelectedButtonUp();
    else if (IsInputStarted<InputAction::Down>())
        cycleSelectedButtonDown();

    for (Button& button : buttons)
        button.update();

    switch (getState())
    {
    case State::MainMenu:
        break;
    case State::Credits:
        if (IsInputStarted<InputAction::Menu>())
        {
            queueState(State::MainMenu);
            SoundEffect::playMulti("sfx_Accept");
        }

        break;
    case State::Playing:
        if (unpauseTime.isExpired() && fullMouseControl && !buttons.size())
            buttons.emplace_back(
                Rectangle{ TILES_X / 2, 1, floor((WINDOW_WIDTH * (1 - 2 * MOUSE_CONTROL_AREA)) / ZOOMED_TILE_DIMENSIONS), 2 },
                "Pause",
                5,
                [] { Game::queuePause(); },
                true);

        if (!gameOver && IsInputStarted<InputAction::Menu>())
        {
            if (paused && unpauseTime.remaining() > COUNTDOWN)
            {
                queueUnpause();
                SoundEffect::playMulti("sfx_Accept");
            }
            else if (!paused)
            {
                queuePause();
                SoundEffect::playMulti("sfx_Accept");
            }
        }
        else if (!gameOver && !paused && !pauseQueued)
        {
            level->update();
            view->update();
            player->update();
            objects.update();
        }

        break;
    }

    allowDestruction = false;
}

void Game::draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    switch (getState())
    {
    case State::MainMenu:
        DrawMenuBackground();
        DrawText(
            GAME_TITLE,
            (LEVEL_WIDTH * ZOOM - MeasureText(GAME_TITLE, 15.0f * ZOOM)) * 0.5f,
            (LEVEL_HEIGHT * 0.3f - 7.5f) * ZOOM,
            15.0f * ZOOM,
            WHITE);
        break;
    case State::Credits:
        DrawMenuBackground();
        DrawCreditsScreen();

        break;
    case State::Playing:
        level->draw();
        objects.draw();
        player->draw();

        if (fullMouseControl)
            DrawMouseControlAreas();

        if (gameOver)
            DrawGameOverScreen();
        else if (paused)
        {
            if (unpauseTime.isOngoing() && unpauseTime.remaining() <= COUNTDOWN)
                DrawInt(ceil(unpauseTime.remaining()), WINDOW_CENTER.x, WINDOW_CENTER.y, 10 * ZOOM);
            else
            {
                DrawUIBox({ TILES_X / 2, TILES_Y / 2, TILES_X - 6, TILES_Y - 6 });
                DrawText(
                    "Paused",
                    (LEVEL_WIDTH * ZOOM - MeasureText("Paused", 10.0f * ZOOM)) * 0.5f,
                    (LEVEL_HEIGHT * 0.25f - 5.0f) * ZOOM,
                    10.0f * ZOOM,
                    WHITE);
            }
        }


        break;
    }

    for (Button& button : buttons) button.draw();

    EndDrawing();
}

void Game::updateTime()
{
    float lastFrame = GetFrameTime();

    frameTime = std::min(MAX_FRAME_TIME, lastFrame);

    if (!(paused || gameOver))
        runTime += frameTime;

    unpausedRunTime += lastFrame;
}

void Game::clearButtons()
{
    buttons.clear();
    selectedButton = 0;
}

void Game::run()
{
    Game& game = instance();

    game.loadTextures();
    game.loadSprites();
    game.loadAnimations();
    game.loadSoundEffects();
    game.initLogic();

    Image icon = LoadImage(FROM_SPRITES_FOLDER("icon.png"));
    SetWindowIcon(icon);

    while (!(WindowShouldClose() || game.shouldExit))
    {
        game.update();

        game.lastMousePosition = game.mousePosition;
        game.lastControllerLeftStickAxis = {
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X),
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) };

        game.draw();

        game.mousePosition = GetMousePosition();

        bool playMusic = !game.unpausedRunTime;

        game.updateTime();

        SoundEffect::update();

        if (playMusic)
            SoundEffect::play("music_Main", true);
    }

    UnloadImage(icon);

    CloseAudioDevice();
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

float Game::unpausedTime()
{
    return instance().unpausedRunTime;
}

void Game::queueState(State newState)
{
    Game& game = instance();

    if (game.queuedState == State::None)
        game.queuedState = newState;
}

void Game::setState(State newState)
{
    Game& game = instance();

    switch (game.getState())
    {
    case State::Playing:
        game.level.release();
        game.view.release();
        game.player.release();
        game.objects.clear();
        game.unpause();
        game.gameOver = false;
        break;
    }

    game.clearButtons();

    switch (newState)
    {
    case State::MainMenu:
    {
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.5f, TILES_X / 2, TILES_Y / 10 },
            "Play",
            5,
            []{ Game::queueState(State::Playing); }
        );
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.6f, TILES_X / 2, TILES_Y / 10 },
            "Credits",
            5,
            []{ Game::queueState(State::Credits); }
        );

        int index = game.buttons.size();
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.7f, TILES_X / 2, TILES_Y / 10 },
            game.fullMouseControl ? "Disable Mouse Controls" : "Enable Mouse Controls",
            5,
            [&game, index]
            {
                Game::toggleMouseControl();
                game.buttons[index].label = game.fullMouseControl ? "Disable Mouse Controls" : "Enable Mouse Controls";
            }
        );

        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.8f, TILES_X / 2, TILES_Y / 10 },
            "Exit",
            5,
            []{ Game::exit(); }
        );

        break;
    }
    case State::Credits:
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.8f, TILES_X / 2, TILES_Y / 10 },
            "Back",
            5,
            []{ Game::queueState(State::MainMenu); });

        break;
    case State::Playing:
        game.level = std::make_unique<Level>();
        game.player = std::make_unique<Player>();
        game.view = std::make_unique<View>();
        game.paused = true;
        game.unpauseTime.start();
        game.spawnTime.start();
        game.deathTime.makeInfinite();

        break;
    }

    game.queuedState = State::None;
    game.StateObject::setState(newState);
}

void Game::flagDestruction()
{
    Game& game = instance();

    if (game.allowDestruction)
        game.destructionFlag = true;
}

bool Game::unflagDestruction()
{
    Game& game = instance();

    if (game.destructionFlag)
    {
        game.destructionFlag = false;
        return true;
    }

    return false;
}

void Game::queueUnpause()
{
    Game& game = instance();

    game.unpauseTime.start();
    game.clearButtons();
}

void Game::pause()
{
    Game& game = instance();
    
    game.paused = true;
    game.pauseQueued = false;
    game.unpauseTime.makeInfinite();
    game.clearButtons();

    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.6f, TILES_X / 2, TILES_Y / 10 },
        "Resume",
        5,
        [] { Game::queueUnpause(); }
    );
    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.7f, TILES_X / 2, TILES_Y / 10 },
        "Restart",
        5,
        [] { Game::queueState(State::Playing); }
    );
    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.8f, TILES_X / 2, TILES_Y / 10 },
        "Quit Run",
        5,
        [] { Game::queueState(State::MainMenu); }
    );
}

void Game::unpause()
{
    Game& game = instance();

    game.paused = false;
    game.clearButtons();
}

void Game::queuePause()
{
    instance().pauseQueued = true;
}

void Game::signalGameOver()
{
    Game& game = instance();

    game.gameOver = true;
    game.deathTime.start();

    game.clearButtons();
    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.7f, TILES_X / 2, TILES_Y / 10 },
        "Restart",
        5,
        [] { Game::queueState(State::Playing); });
    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.8f, TILES_X / 2, TILES_Y / 10 },
        "Back to Menu",
        5,
        [] { Game::queueState(State::MainMenu); });
}

void Game::cycleSelectedButtonUp()
{
    if (instance().buttons.size())
        selectButton((getSelectedButtonIndex() - 1 + getNextButtonIndex()) % getNextButtonIndex());
}

void Game::cycleSelectedButtonDown()
{
    if (instance().buttons.size())
        selectButton((getSelectedButtonIndex() + 1) % getNextButtonIndex());
}

int Game::getNextButtonIndex()
{
    return instance().buttons.size();
}

int Game::getSelectedButtonIndex()
{
    return instance().selectedButton;
}

void Game::selectButton(int index)
{
    Game& game = instance();

    if (index < 0 || index >= game.buttons.size())
        return;
    
    if (game.selectedButton != -1)
        game.buttons[game.selectedButton].selected = false;

    game.buttons[game.selectedButton = index].select();
}

void Game::toggleMouseControl()
{
    Game& game = instance();

    game.fullMouseControl = !game.fullMouseControl;
}

bool Game::isFullyMouseControllable()
{
    return instance().fullMouseControl;
}

Vector2 Game::getMousePosition()
{
    return instance().mousePosition;
}

Vector2 Game::getLastMousePosition()
{
    return instance().lastMousePosition;
}

Vector2 Game::getLastControllerLeftStickAxis()
{
    return instance().lastControllerLeftStickAxis;
}

float Game::getSpawnTime()
{
    return instance().spawnTime.getStartTime();
}

float Game::getDeathTime()
{
    return instance().deathTime.getStartTime();
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