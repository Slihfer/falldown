#pragma once

#include "core/Game.h"

class Timepoint
{
protected:
    float startTime;

public:
    explicit Timepoint(float startTime = Game::time());

    void start();

    float expired();
};