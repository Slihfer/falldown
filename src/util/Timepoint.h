#pragma once

class Timepoint
{
protected:
    float startTime;

public:
    explicit Timepoint(float startTime = currentTime());
    void start();
    float expired();

    static float currentTime();
};