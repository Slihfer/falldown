#pragma once

#include "Timepoint.h"

#include <limits>

class Duration : public Timepoint
{
public:
    using Timepoint::start;

private:
    float duration;

public:
    explicit Duration(float duration, float startTime = -std::numeric_limits<float>::infinity());

    void setDuration(float newDuration, bool keepRemainingTime = false);

    void start(float newDuration);
    bool startIfExpired();
    void end();

    bool isOngoing();
    bool isExpired();
    float remaining();
    float getDuration();
};