#include "Timepoint.h"

Timepoint::Timepoint(float startTime) : startTime(startTime) {}

void Timepoint::start()
{
    startTime = Game::time();
}

float Timepoint::expired()
{
    return Game::time() - startTime;
}
