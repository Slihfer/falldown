#pragma once

#include <memory>

#include "level/Level.h"
#include "draw/View.h"
#include "objects/Player.h"
#include "objects/Blob.h"

class Game
{
//Members
private:
    float frameTime;
    float runTime;

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

    static Level& getLevel();
    static View& getView();
    static Player& getPlayer();

    template <class ... TArgs>
    static void spawnBlob(TArgs&& ... args)
    {
        instance().blobs.emplace_back(std::forward<TArgs>(args) ...);
    }
};