#pragma once

#include <memory>

#include "screens/Level.h"
#include "draw/View.h"
#include "objects/Player.h"
#include "objects/Blob.h"
#include "objects/GhostPowerup.h"
#include "objects/VoidPowerup.h"
#include "objects/Button.h"
#include "objects/Spikes.h"
#include "objects/Turret.h"
#include "util/ObjectContainer.h"

constexpr int TARGET_FPS = 60;
constexpr float TARGET_FRAME_TIME = 1.0f / TARGET_FPS;
constexpr float MAX_FRAME_TIME = 0.05f;
constexpr float COUNTDOWN = 3;

enum class GameState
{
    None,
    MainMenu,
    Credits,
    Playing
};

class Game : public StateObject<GameState>
{
//Types
public:
    using State = GameState;

//Members
private:
    bool shouldExit;
    float frameTime;
    float runTime;
    float unpausedRunTime;
    bool allowDestruction;
    bool destructionFlag;
    bool paused;
    bool pauseQueued;
    Duration unpauseTime;
    State queuedState;
    bool gameOver;
    bool fullMouseControl;
    int selectedButton;
    Vector2 mousePosition;
    Vector2 lastMousePosition;
    Vector2 lastControllerLeftStickAxis;
    Timepoint spawnTime;
    Timepoint deathTime;

    ObjectContainer<
        Blob,
        GhostPowerup,
        VoidPowerup,
        Spikes,
        Turret> objects;

    std::unique_ptr<Level> level;
    std::unique_ptr<View> view;
    std::unique_ptr<Player> player;

    std::vector<Button> buttons;

//Constructors/Destructors
private:
    Game();
    ~Game();

public:
    Game(Game&) = delete;
    
//Instance Methods
private:
    void loadTextures();
    void loadSprites();
    void loadAnimations();
    void loadSoundEffects();
    void initLogic();

    void update();
    void draw();

    void updateTime();

    template <class T>
    void updateDestructibles(std::vector<T>& destructibles)
    {
        for (auto it = destructibles.begin(); it != destructibles.end();)
        {
            it->update();

            if (destructionFlag)
            {
                it = destructibles.erase(it);
                destructionFlag = false;
            }
            else
            {
                ++it;
            }
        }
    }
    
    void clearButtons();

//Class Methods
public:
    static inline Game& instance()
    {
        static Game game;
        return game;
    }

    static void run();
    static void exit();
    static float delta();
    static float time();
    static float unpausedTime();
    static void queueState(State newState);
    static void setState(State newState);
    static void flagDestruction();
    static bool unflagDestruction();
    static void pause();
    static void unpause();
    static void queuePause();
    static void queueUnpause();

    static void signalGameOver();
    static void cycleSelectedButtonUp();
    static void cycleSelectedButtonDown();
    static int getNextButtonIndex();
    static int getSelectedButtonIndex();
    static void selectButton(int index);
    static void toggleMouseControl();
    static bool isFullyMouseControllable();
    static Vector2 getMousePosition();
    static Vector2 getLastMousePosition();
    static Vector2 getLastControllerLeftStickAxis();
    static float getSpawnTime();
    static float getDeathTime();

    static Level& getLevel();
    static View& getView();
    static Player& getPlayer();

    template <class TType, class ... TArgs>
    static void spawn(TArgs&& ... args)
    {
        instance().objects.getContainer<TType>().emplace_back(std::forward<TArgs>(args) ...);
    }
};