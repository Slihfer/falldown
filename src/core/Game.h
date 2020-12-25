#pragma once

#include "level/Level.h"
#include "draw/View.h"
#include "objects/Player.h"

class Game
{
//Members
private:
    Level level;
    View view;
    Player player;

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

    void update(float t);
    void draw();

//Class Methods
public:
    static inline Game& instance()
    {
        static Game game;
        return game;
    }

    static void run();

    static View& getView();
    static Level& getLevel();
    static Player& getPlayer();
};