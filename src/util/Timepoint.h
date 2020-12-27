#pragma once

class Timepoint
{
protected:
    float startTime;

public:
    explicit Timepoint(float startTime = currentTime());
    void start();
    float elapsed();

    static float currentTime();
};