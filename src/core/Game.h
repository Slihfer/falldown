#pragma once

#include "level/level.h"

class Game
{
//Members
private:
    TileGrid level;

//Constructors/Destructors
private:
    Game();
    ~Game();

public:
    Game(Game&) = delete;
    
//Instance Methods
private:
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
};