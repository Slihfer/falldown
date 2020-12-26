#include "Duration.h"

#include "core/Game.h"

Duration::Duration(float duration, float startTime) : Timepoint(startTime), duration(std::max(0.0f, duration)) {}

void Duration::setDuration(float newDuration, bool keepRemainingTime)
{
    newDuration = std::max(0.0f, newDuration);
    
    if (keepRemainingTime)
        startTime += duration - newDuration;

    duration = newDuration;
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

bool Duration::isRunning()
{
    return expired() < duration;
}

bool Duration::isExpired()
{
    return !isRunning();
}

float Duration::remaining()
{
    return std::max(0.0f, duration - expired());
}