#pragma once

#define SETUP 0

#if SETUP
#define FROM_GAME_FOLDER(path) (std::string(GetWorkingDirectory()).append("/").append(path)).c_str()
#define FROM_ASSSETS_FOLDER(path) (std::string(GetWorkingDirectory()).append("/assets/").append(path)).c_str()
#define FROM_SPRITES_FOLDER(path) (std::string(GetWorkingDirectory()).append("/assets/graphics/sprites/").append(path)).c_str()
#define FROM_TEXTURES_FOLDER(path) (std::string(GetWorkingDirectory()).append("/assets/graphics/textures/").append(path)).c_str()
#define FROM_MUSIC_FOLDER(path) (std::string(GetWorkingDirectory()).append("/assets/audio/music/").append(path)).c_str()
#define FROM_SFX_FOLDER(path) (std::string(GetWorkingDirectory()).append("/assets/audio/sfx/").append(path)).c_str()
#else
#define FROM_GAME_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../").append(path)).c_str()
#define FROM_ASSSETS_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../assets/").append(path)).c_str()
#define FROM_SPRITES_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../assets/graphics/sprites/").append(path)).c_str()
#define FROM_TEXTURES_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../assets/graphics/textures/").append(path)).c_str()
#define FROM_MUSIC_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../assets/audio/music/").append(path)).c_str()
#define FROM_SFX_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../assets/audio/sfx/").append(path)).c_str()
#endif