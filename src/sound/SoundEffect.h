#pragma once

#include <string>

#include <raylib.h>

#include "util/Resource.h"
#include "util/Duration.h"

class SoundEffect : public Resource<SoundEffect>
{
private:
    Sound sound;
    Duration duration;
    bool repeat;

public:
    SoundEffect(const std::string& filePath);
    ~SoundEffect();

public:
    static void play(const std::string& key, bool repeat = false);
    static void stop(const std::string& key);
    static void playMulti(const std::string& key);
    static void stopMulti();

    static void update();
};