#pragma once

#define FROM_GAME_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../../").append(path)).c_str()
#define FROM_ASSSETS_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../../assets/").append(path)).c_str()
#define FROM_ASSSETS_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../../assets/sprites").append(path)).c_str()
#define FROM_ASSSETS_FOLDER(path) (std::string(GetWorkingDirectory()).append("/../../../../../assets/sounds").append(path)).c_str()