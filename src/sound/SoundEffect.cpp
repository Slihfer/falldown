#include "SoundEffect.h"

#include "core/Game.h"

SoundEffect::SoundEffect(const std::string& filePath) :
    sound(LoadSound(filePath.c_str())),
    duration(0),
    repeat(false)
{
    Music tmp = LoadMusicStream(filePath.c_str());
    duration = Duration(GetMusicTimeLength(tmp) - TARGET_FRAME_TIME, true);
    UnloadMusicStream(tmp);
}

SoundEffect::~SoundEffect()
{
    //Unloading crashes Raylib ¯\_(ツ)_/¯
    //UnloadSound(sound);
}

void SoundEffect::play(const std::string& key, bool repeat)
{
    SoundEffect& soundEffect = const_cast<SoundEffect&>(get(key));

    PlaySound(soundEffect.sound);
    soundEffect.duration.start();
    soundEffect.repeat = repeat;
}

void SoundEffect::stop(const std::string& key)
{
    StopSound(get(key).sound);
}

void SoundEffect::playMulti(const std::string& key)
{
    PlaySoundMulti(get(key).sound);
}

void SoundEffect::stopMulti()
{
    StopSoundMulti();
}

void SoundEffect::update()
{
    for (const auto& p : getContainer())
        if (p.second.repeat && p.second.duration.isExpired())
            play(p.first, true);
}
