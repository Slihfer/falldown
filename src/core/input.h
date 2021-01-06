#pragma once

#include <raylib.h>

#include "core/Game.h"

#define MOUSE_INDICATOR 1

constexpr float CONTROLLER_DEADZONE = 0.2f;
constexpr float MOUSE_CONTROL_AREA = 0.4f;
constexpr Color MOUSE_CONTROL_AREA_HIGHLIGHT{ 255, 255, 255, 19 };
constexpr Color MOUSE_CONTROL_SEPARATOR{ 255, 255, 255, 63 };

Rectangle GetLeftMouseControlArea();
Rectangle GetRightMouseControlArea();

void DrawMouseControlAreas();

enum class InputAction
{
    Left,
    Right,
    Up,
    Down,
    Jump,
    Select,
    Menu
};

template <InputAction TAction>
bool IsInputStarted();

template <InputAction TAction>
bool IsInputEnded();

template <InputAction TAction>
bool IsInputActive();

template <InputAction TAction>
inline bool IsInputInactive()
{
    return !IsInputActive<TAction>();
}



//////////Left//////////
template <>
inline bool IsInputStarted<InputAction::Left>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().x >= -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -CONTROLLER_DEADZONE
        ) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
    //Mouse
        (
            Game::isFullyMouseControllable() &&
            !CheckCollisionPointRec(Game::getLastMousePosition(), GetLeftMouseControlArea()) &&
            CheckCollisionPointRec(Game::getMousePosition(), GetLeftMouseControlArea())
        );
}

template <>
inline bool IsInputEnded<InputAction::Left>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_A) || IsKeyReleased(KEY_LEFT) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().x < -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= -CONTROLLER_DEADZONE
        ) || IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
    //Mouse
        (
            Game::isFullyMouseControllable() &&
            CheckCollisionPointRec(Game::getLastMousePosition(), GetLeftMouseControlArea()) &&
            !CheckCollisionPointRec(Game::getMousePosition(), GetLeftMouseControlArea())
        );
}

template <>
inline bool IsInputActive<InputAction::Left>()
{
    return
        //Keyboard
        IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ||
        //Gamepad
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -CONTROLLER_DEADZONE ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
        //Mouse
        (
            Game::isFullyMouseControllable() &&
            CheckCollisionPointRec(Game::getMousePosition(), GetLeftMouseControlArea())
            );
}



//////////Right//////////
template <>
inline bool IsInputStarted<InputAction::Right>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().x <= CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > CONTROLLER_DEADZONE
        ) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
    //Mouse
        (
            Game::isFullyMouseControllable() &&
            !CheckCollisionPointRec(Game::getLastMousePosition(), GetRightMouseControlArea()) &&
            CheckCollisionPointRec(Game::getMousePosition(), GetRightMouseControlArea())
        );
}

template <>
inline bool IsInputEnded<InputAction::Right>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_D) || IsKeyReleased(KEY_RIGHT) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().x > CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= CONTROLLER_DEADZONE
        ) || IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
    //Mouse
        (
            Game::isFullyMouseControllable() &&
            CheckCollisionPointRec(Game::getLastMousePosition(), GetRightMouseControlArea()) &&
            !CheckCollisionPointRec(Game::getMousePosition(), GetRightMouseControlArea())
        );
}

template <>
inline bool IsInputActive<InputAction::Right>()
{
    return
    //Keyboard
        IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ||
    //Gamepad
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > CONTROLLER_DEADZONE ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
    //Mouse
        (
            Game::isFullyMouseControllable() &&
            CheckCollisionPointRec(Game::getMousePosition(), GetRightMouseControlArea())
        );
}



//////////Up//////////
template <>
inline bool IsInputStarted<InputAction::Up>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().y >= -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -CONTROLLER_DEADZONE
        ) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
}

template <>
inline bool IsInputEnded<InputAction::Up>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().y < -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= -CONTROLLER_DEADZONE
        ) || IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
}

template <>
inline bool IsInputActive<InputAction::Up>()
{
    return
    //Keyboard
        IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ||
    //Gamepad
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -CONTROLLER_DEADZONE ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
}



//////////Down//////////
template <>
inline bool IsInputStarted<InputAction::Down>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().y <= CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > CONTROLLER_DEADZONE
        ) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
}

template <>
inline bool IsInputEnded<InputAction::Down>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_S) || IsKeyReleased(KEY_DOWN) ||
    //Gamepad
        (
            Game::getLastControllerLeftStickAxis().y > CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= CONTROLLER_DEADZONE
        ) || IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
}

template <>
inline bool IsInputActive<InputAction::Down>()
{
    return
    //Keyboard
        IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ||
    //Gamepad
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > CONTROLLER_DEADZONE ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
}



//////////Jump//////////
template <>
inline bool IsInputStarted<InputAction::Jump>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_K) || IsKeyPressed(KEY_SPACE) ||
    //Gamepad
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
    //Mouse
        (Game::isFullyMouseControllable() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

template <>
inline bool IsInputEnded<InputAction::Jump>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_K) || IsKeyReleased(KEY_SPACE) ||
    //Gamepad
        IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
    //Mouse
        (Game::isFullyMouseControllable() && IsMouseButtonReleased(MOUSE_LEFT_BUTTON));
}

template <>
inline bool IsInputActive<InputAction::Jump>()
{
    return
        //Keyboard
        IsKeyDown(KEY_K) || IsKeyDown(KEY_SPACE) ||
        //Gamepad
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
        //Mouse
        (Game::isFullyMouseControllable() && IsMouseButtonDown(MOUSE_LEFT_BUTTON));
}



//////////Select//////////
template <>
inline bool IsInputStarted<InputAction::Select>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_K) || IsKeyPressed(KEY_ENTER) ||
    //Gamepad
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
}

template <>
inline bool IsInputEnded<InputAction::Select>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_K) || IsKeyReleased(KEY_ENTER) ||
    //Gamepad
        IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
}

template <>
inline bool IsInputActive<InputAction::Select>()
{
    return
    //Keyboard
        IsKeyDown(KEY_K) || IsKeyDown(KEY_ENTER) ||
    //Gamepad
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
}



//////////Menu//////////
template <>
inline bool IsInputStarted<InputAction::Menu>()
{
    return
    //Keyboard
        IsKeyPressed(KEY_ESCAPE) ||
    //Gamepad
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_LEFT) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
}

template <>
inline bool IsInputEnded<InputAction::Menu>()
{
    return
    //Keyboard
        IsKeyReleased(KEY_ESCAPE) ||
    //Gamepad
        IsGamepadButtonReleased(0, GAMEPAD_BUTTON_MIDDLE) ||
        IsGamepadButtonReleased(0, GAMEPAD_BUTTON_MIDDLE_LEFT) ||
        IsGamepadButtonReleased(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
}

template <>
inline bool IsInputActive<InputAction::Menu>()
{
    return
    //Keyboard
        IsKeyDown(KEY_ESCAPE) ||
    //Gamepad
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE) ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_LEFT) ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
}