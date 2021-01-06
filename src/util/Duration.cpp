#include "Duration.h"

#include "core/Game.h"

Duration::Duration(float duration, float startTime, bool useUnpausedTime) :
    Timepoint(startTime, useUnpausedTime),
    duration(std::max(0.0f, duration)) {}

Duration::Duration(float duration, bool useUnpausedTime) :
    Timepoint(-std::numeric_limits<float>::infinity(), useUnpausedTime),
    duration(duration) {}

void Duration::setDuration(float newDuration, bool keepRemainingTime)
{
    newDuration = std::max(0.0f, newDuration);
    
    if (keepRemainingTime)
        startTime += duration - newDuration;

    duration = newDuration;
}

void Duration::start(float newDuration)
{
    setDuration(newDuration);
    start();
}

bool Duration::startIfExpired()
{
    if (isExpired())
    {
        start();
        return true;
    }

    return false;
}

void Duration::end()
{
    startTime = -std::numeric_limits<float>::infinity();
}

bool Duration::isOngoing() const
{
    return elapsed() < duration;
}

bool Duration::isExpired() const
{
    return !isOngoing();
}

float Duration::remaining() const
{
    return std::max(0.0f, duration - elapsed());
}

float Duration::getDuration() const
{
    return duration;
}
