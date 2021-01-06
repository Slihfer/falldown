#include "TImepoint.h"

#include "core/Game.h"

Timepoint::Timepoint(bool useUnpausedTime) :
    startTime(useUnpausedTime ? Game::unpausedTime() : Game::time()),
    useUnpausedTime(useUnpausedTime) {}

Timepoint::Timepoint(float startTime, bool useUnpausedTime) :
    startTime(startTime),
    useUnpausedTime(useUnpausedTime) {}

void Timepoint::start()
{
    startTime = getCurrentTime();
}

void Timepoint::makeInfinite()
{
    startTime = std::numeric_limits<float>::infinity();
}

float Timepoint::elapsed() const
{
    return getCurrentTime() - startTime;
}

float Timepoint::getStartTime() const
{
    return startTime;
}

float Timepoint::getCurrentTime() const
{
    return useUnpausedTime ? Game::unpausedTime() : Game::time();
}
