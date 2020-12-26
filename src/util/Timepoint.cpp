#include "TImepoint.h"

#include "core/Game.h"

Timepoint::Timepoint(float startTime) : startTime(startTime) {}

void Timepoint::start()
{
    startTime = Game::time();
}

float Timepoint::expired()
{
    return Game::time() - startTime;
}

float Timepoint::currentTime()
{
    return Game::time();
}
