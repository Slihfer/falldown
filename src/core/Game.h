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
    bool gameOver;
    int selectedButton;

    std::vector<Button> buttons;
    std::unique_ptr<Level> level;
    std::unique_ptr<View> view;
    std::unique_ptr<Player> player;
    std::vector<Blob> blobs;
    std::vector<GhostPowerup> ghostPowerups;
    std::vector<VoidPowerup> voidPowerups;
    std::vector<Spikes> spikes;
    std::vector<Turret> turrets;

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
    void initObjects();

    void update();
    void draw();

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
    static void setState(State newState);
    static void flagDestruction();

    static void pause();
    static void unpause();
    static void signalGameOver();
    static void cycleSelectedButtonUp();
    static void cycleSelectedButtonDown();
    static int getNextButtonIndex();
    static int getSelectedButtonIndex();
    static void selectButton(int index);

    static Level& getLevel();
    static View& getView();
    static Player& getPlayer();

    template <class ... TArgs>
    static void spawnBlob(TArgs&& ... args)
    {
        instance().blobs.emplace_back(std::forward<TArgs>(args) ...);
    }

    template <class ... TArgs>
    static void spawnGhostPowerup(TArgs&& ... args)
    {
        instance().ghostPowerups.emplace_back(std::forward<TArgs>(args) ...);
    }

    template <class ... TArgs>
    static void spawnVoidPowerup(TArgs&& ... args)
    {
        instance().voidPowerups.emplace_back(std::forward<TArgs>(args) ...);
    }

    template <class ... TArgs>
    static void spawnSpikes(TArgs&& ... args)
    {
        instance().spikes.emplace_back(std::forward<TArgs>(args) ...);
    }

    template <class ... TArgs>
    static void spawnTurret(TArgs&& ... args)
    {
        instance().turrets.emplace_back(std::forward<TArgs>(args) ...);
    }
};