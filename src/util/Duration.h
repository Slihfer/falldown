#pragma once

#include "Timepoint.h"

#include <limits>

class Duration : public Timepoint
{
private:
    float duration;

public:
    explicit Duration(float duration, float startTime = -std::numeric_limits<float>::infinity());

    void setDuration(float newDuration, bool keepRemainingTime = false);

    bool startIfExpired();
    void end();

    bool isRunning();
    bool isExpired();
    float remaining();
};