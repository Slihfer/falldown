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
    explicit Duration(
        float duration,
        float startTime = -std::numeric_limits<float>::infinity(),
        bool useUnpausedTime = false);

    explicit Duration(
        float duration,
        bool useUnpausedTime);

    void setDuration(float newDuration, bool keepRemainingTime = false);

    void start(float newDuration);
    bool startIfExpired();
    void end();

    bool isOngoing() const;
    bool isExpired() const;
    float remaining() const;
    float getDuration() const;
};