#include "Animation.h"

void Animation::constructFrames()
{
    for (const Frame& f : frames)
        duration += f.duration;
}

const Sprite& Animation::getCurrentSprite(float animTime, bool loop) const
{
    if (loop)
        animTime = fmodf(animTime, duration);

    float acc = 0.0f;

    for (const Frame& f : frames)
        if (animTime < (acc += f.duration))
            return f.sprite;

    return frames.back().sprite;
}

float Animation::getDuration() const
{
    return duration;
}