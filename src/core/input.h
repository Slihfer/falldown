#pragma once

#include <raylib.h>

#include "core/Game.h"

constexpr float CONTROLLER_DEADZONE = 0.2f;
constexpr float MOUSE_CONTROL_AREA = 0.4f;
constexpr Color MOUSE_CONTROL_AREA_LEFT_COLOR{ 255, 63, 63, 40 };
constexpr Color MOUSE_CONTROL_AREA_RIGHT_COLOR{ 63, 63, 255, 40 };

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
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_A) ||
            IsKeyPressed(KEY_LEFT);
    case InputType::Mouse:
        return
            !CheckCollisionPointRec(Game::getLastMousePosition(), GetLeftMouseControlArea()) &&
            CheckCollisionPointRec(Game::getMousePosition(), GetLeftMouseControlArea());
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().x >= -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -CONTROLLER_DEADZONE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    }
    
    return false;
}

template <>
inline bool IsInputEnded<InputAction::Left>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_A) ||
            IsKeyReleased(KEY_LEFT);
    case InputType::Mouse:
        return
            CheckCollisionPointRec(Game::getLastMousePosition(), GetLeftMouseControlArea()) &&
            !CheckCollisionPointRec(Game::getMousePosition(), GetLeftMouseControlArea());
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().x < -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= -CONTROLLER_DEADZONE) ||
            IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    }

    return false;
}

template <>
inline bool IsInputActive<InputAction::Left>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_LEFT);

    case InputType::Mouse:
        return CheckCollisionPointRec(Game::getMousePosition(), GetLeftMouseControlArea());
    case InputType::Controller:
        return
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -CONTROLLER_DEADZONE ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    }

    return false;
}



//////////Right//////////
template <>
inline bool IsInputStarted<InputAction::Right>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_D) ||
            IsKeyPressed(KEY_RIGHT);
    case InputType::Mouse:
        return
            !CheckCollisionPointRec(Game::getLastMousePosition(), GetRightMouseControlArea()) &&
            CheckCollisionPointRec(Game::getMousePosition(), GetRightMouseControlArea());
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().x <= CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > CONTROLLER_DEADZONE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }

    return false;
}

template <>
inline bool IsInputEnded<InputAction::Right>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_D) ||
            IsKeyReleased(KEY_RIGHT);
    case InputType::Mouse:
        return
            CheckCollisionPointRec(Game::getLastMousePosition(), GetRightMouseControlArea()) &&
            !CheckCollisionPointRec(Game::getMousePosition(), GetRightMouseControlArea());
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().x > CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= CONTROLLER_DEADZONE) ||
            IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }

    return false;
}

template <>
inline bool IsInputActive<InputAction::Right>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_D) ||
            IsKeyDown(KEY_RIGHT);
    case InputType::Mouse:
        return CheckCollisionPointRec(Game::getMousePosition(), GetRightMouseControlArea());
    case InputType::Controller:
        return
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > CONTROLLER_DEADZONE ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }

    return false;
}



//////////Up//////////
template <>
inline bool IsInputStarted<InputAction::Up>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_W) ||
            IsKeyPressed(KEY_UP);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().y >= -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -CONTROLLER_DEADZONE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
    }

    return false;
}

template <>
inline bool IsInputEnded<InputAction::Up>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_W) ||
            IsKeyReleased(KEY_UP);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().y < -CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= -CONTROLLER_DEADZONE) ||
            IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
    }

    return false;
}

template <>
inline bool IsInputActive<InputAction::Up>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_W) ||
            IsKeyDown(KEY_UP);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -CONTROLLER_DEADZONE ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
    }

    return false;
}



//////////Down//////////
template <>
inline bool IsInputStarted<InputAction::Down>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_S) ||
            IsKeyPressed(KEY_DOWN);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().y <= CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > CONTROLLER_DEADZONE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    }

    return false;
}

template <>
inline bool IsInputEnded<InputAction::Down>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_S) ||
            IsKeyReleased(KEY_DOWN);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return
            (Game::getLastControllerLeftStickAxis().y > CONTROLLER_DEADZONE &&
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= CONTROLLER_DEADZONE) ||
            IsGamepadButtonReleased(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    }

    return false;
}

template <>
inline bool IsInputActive<InputAction::Down>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_S) ||
            IsKeyDown(KEY_DOWN);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > CONTROLLER_DEADZONE ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    }

    return false;
}



//////////Jump//////////
template <>
inline bool IsInputStarted<InputAction::Jump>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_K) ||
            IsKeyPressed(KEY_SPACE);
    case InputType::Mouse:
        return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    case InputType::Controller:
        return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }

    return false;
}

template <>
inline bool IsInputEnded<InputAction::Jump>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_K) ||
            IsKeyReleased(KEY_SPACE);
    case InputType::Mouse:
        return IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    case InputType::Controller:
        return IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }

    return false;
}

template <>
inline bool IsInputActive<InputAction::Jump>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_K) ||
            IsKeyDown(KEY_SPACE);
    case InputType::Mouse:
        return IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    case InputType::Controller:
        return IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }

    return false;
}



//////////Select//////////
template <>
inline bool IsInputStarted<InputAction::Select>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_K) ||
            IsKeyPressed(KEY_ENTER);
    case InputType::Mouse:
        return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    case InputType::Controller:
        return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }

    return false;
}

template <>
inline bool IsInputEnded<InputAction::Select>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_K) ||
            IsKeyReleased(KEY_ENTER);
    case InputType::Mouse:
        return IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    case InputType::Controller:
        return IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }

    return false;
}

template <>
inline bool IsInputActive<InputAction::Select>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_K) ||
            IsKeyDown(KEY_ENTER);
    case InputType::Mouse:
        return IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    case InputType::Controller:
        return IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }
        return false;
}



//////////Menu//////////
template <>
inline bool IsInputStarted<InputAction::Menu>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyPressed(KEY_ESCAPE);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    }

    return false;
}

template <>
inline bool IsInputEnded<InputAction::Menu>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyReleased(KEY_ESCAPE);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return IsGamepadButtonReleased(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    }
    
    return false;
}

template <>
inline bool IsInputActive<InputAction::Menu>()
{
    switch (Game::getInputType())
    {
    case InputType::Keyboard:
        return
            IsKeyDown(KEY_ESCAPE);
    case InputType::Mouse:
        break;
    case InputType::Controller:
        return IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    }
    
    return false;
}