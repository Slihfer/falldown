#pragma once

#include <memory>

#include "level/Level.h"
#include "draw/View.h"
#include "objects/Player.h"
#include "objects/Blob.h"
#include "objects/Button.h"

class Game
{
//Types
public:
    enum State
    {
        None,
        MainMenu,
        Playing
    };

//Members
private:
    float frameTime;
    float runTime;
    bool allowDestruction;
    State state;
    bool destructionFlag;

    std::vector<Button> buttons;
    std::unique_ptr<Level> level;
    std::unique_ptr<View> view;
    std::unique_ptr<Player> player;
    std::vector<Blob> blobs;

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
    static float delta();
    static float time();
    static void switchState(State state);

    static void flagDestruction();

    static Level& getLevel();
    static View& getView();
    static Player& getPlayer();

    template <class ... TArgs>
    static void spawnBlob(TArgs&& ... args)
    {
        instance().blobs.emplace_back(std::forward<TArgs>(args) ...);
    }
};