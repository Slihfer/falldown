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
#include "screens/Credits.h"
#include "screens/GameOver.h"
#include "screens/MenuBackground.h"

Game::Game() :
    StateObject(State::None, 0),
    inputType(InputType::Controller),
    shouldExit(false),
    frameTime(0),
    runTime(0),
    unpausedRunTime(0),
    allowDestruction(false),
    destructionFlag(false),
    paused(false),
    gameOver(false),
    selectedButton(0),
    objects(),
    mousePosition{ -1.0f, -1.0f },
    lastMousePosition{ -1.0f, -1.0f },
    lastControllerLeftStickAxis{}
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
        break;
    case State::Playing:
        if (!gameOver && IsInputStarted<InputAction::Menu>())
            if (paused)
                unpause();
            else
                pause();

        if (!(paused || gameOver))
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
        break;
    case State::Credits:
        DrawMenuBackground();
        DrawCreditsScreen();

        break;
    case State::Playing:
        level->draw();
        objects.draw();
        player->draw();

        if (gameOver)
            DrawGameOverScreen();
        else if (paused)
            DrawUIBox({ TILES_X / 2, TILES_Y / 2, TILES_X - 6, TILES_Y - 6 });
        else if (inputType == InputType::Mouse)
            DrawMouseControlAreas();

        break;
    }

    for (Button& button : buttons) button.draw();

    EndDrawing();
}

void Game::clearButtons()
{
    buttons.clear();
    selectedButton = inputType == InputType::Mouse ? -1 : 0;
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

        if (!(game.paused || game.gameOver))
            game.runTime += game.frameTime;

        game.unpausedRunTime += game.frameTime;

        game.update();

        game.lastMousePosition = game.mousePosition;
        game.lastControllerLeftStickAxis = {
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X),
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) };

        game.draw();

        game.mousePosition = GetMousePosition();
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

float Game::unpausedTime()
{
    return instance().unpausedRunTime;
}

void Game::setState(State newState)
{
    Game& game = instance();

    switch (game.getState())
    {
    case State::MainMenu:
        break;
    case State::Playing:
        game.level.release();
        game.view.release();
        game.player.release();
        game.objects.clear();
        unpause();
        game.gameOver = false;
        break;
    }

    game.clearButtons();

    switch (newState)
    {
    case State::MainMenu:
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.4f, TILES_X / 2, TILES_Y / 10 },
            "Play",
            5,
            []{ Game::setState(State::Playing); }
        );
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.5f, TILES_X / 2, TILES_Y / 10 },
            "Credits",
            5,
            []{ Game::setState(State::Credits); }
        );
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.6f, TILES_X / 2, TILES_Y / 10 },
            "Exit",
            5,
            []{ Game::exit(); }
        );

        break;
    case State::Credits:
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.8f, TILES_X / 2, TILES_Y / 10 },
            "Back",
            5,
            []{ Game::setState(State::MainMenu); });

        break;
    case State::Playing:
        game.level = std::make_unique<Level>();
        game.player = std::make_unique<Player>();
        game.view = std::make_unique<View>();

        if (getInputType() == InputType::Mouse)
            game.buttons.emplace_back(
                Rectangle{ TILES_X / 2, TILES_Y * 0.1f, TILES_X / 2, TILES_Y / 10 },
                "Pause",
                5,
                [] { Game::pause(); });

        break;
    }

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

InputType Game::getInputType()
{
    return instance().inputType;
}

void Game::cycleInputType()
{
    Game& game = instance();

    game.inputType = static_cast<InputType>((static_cast<int>(game.inputType) + 1) % static_cast<int>(InputType::Count));
}

void Game::pause()
{
    Game& game = instance();
    
    game.paused = true;
    game.clearButtons();

    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.4f, TILES_X / 2, TILES_Y / 10 },
        "Resume",
        5,
        [] { Game::unpause(); }
    );
    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.6f, TILES_X / 2, TILES_Y / 10 },
        "Quit Run",
        5,
        [] { Game::setState(State::MainMenu); }
    );
}

void Game::unpause()
{
    Game& game = instance();

    game.paused = false;
    game.clearButtons();

    if (getInputType() == InputType::Mouse)
        game.buttons.emplace_back(
            Rectangle{ TILES_X / 2, TILES_Y * 0.1f, TILES_X / 2, TILES_Y / 10 },
            "Pause",
            5,
            [] { Game::pause(); });
}

void Game::signalGameOver()
{
    Game& game = instance();

    game.gameOver = true;

    game.clearButtons();
    game.buttons.emplace_back(
        Rectangle{ TILES_X / 2, TILES_Y * 0.8f, TILES_X / 2, TILES_Y / 10 },
        "Back",
        5,
        [] { Game::setState(State::MainMenu); });
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

    game.buttons[game.selectedButton = index].selected = true;
}

void Game::deselectButton(int index)
{
    Game& game = instance();

    if (index != game.selectedButton)
        return;

    game.buttons[game.selectedButton].selected = false;

    game.selectedButton = -1;
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