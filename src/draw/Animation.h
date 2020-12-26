#pragma once

#include "Sprite.h"

class Animation : public Resource<Animation>
{
public:
    struct Frame
    {
        Sprite sprite;
        float duration;
    };

private:
    std::vector<Frame> frames;
    float duration;

    template <class ... TArgs>
    void constructFrames(Frame frame, TArgs ... args)
    {
        frames.push_back(frame);
        constructFrames(args ...);
    }

    void constructFrames();

public:
    template <class ... TArgs>
    Animation(TArgs ... args) : frames(), duration(0)
    {
        constructFrames(args ...);
    }

    const Sprite& getCurrentSprite(float animTime, bool loop = false) const;
    float getDuration() const;
};