#pragma once

class Timepoint
{
protected:
    float startTime;
    bool useUnpausedTime;

public:
    explicit Timepoint(bool useUnpausedTime = false);
    explicit Timepoint(float startTime, bool useUnpausedTime = false);
    void start();
    void makeInfinite();
    float elapsed() const;
    float getStartTime() const;
    float getCurrentTime() const;
};