#include "Button.h"

#include "core/Game.h"
#include "core/input.h"
#include "draw/draw.h"
#include "util/rectangle.h"

Button::Button(
    Rectangle shape,
    const std::string& label,
    int fontSize,
    const std::function<void()>& action,
    bool mouseOnly) :
    shape(shape),
    label(label),
    fontSize(fontSize),
    action(action),
    index(Game::getNextButtonIndex()),
    selected(Game::getSelectedButtonIndex() == index),
    mouseOnly(mouseOnly) {}

void Button::update()
{
    if (mouseOnly)
        selected = false;

    if (!mouseOnly && selected && IsInputStarted<InputAction::Select>())
        action();
    else if (
        CheckCollisionPointRec(
            Game::getMousePosition(),
            AssembleRectangle(
                (GetRectanglePosition(shape) - 0.5f * GetRectangleDimensions(shape)) * TILE_DIMENSIONS * ZOOM,
                GetRectangleDimensions(shape) * ZOOM * TILE_DIMENSIONS)))
    {
        Game::selectButton(index);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            action();
    }
}

void Button::draw()
{
    for (int i = 1; i < shape.width - 1; ++i)
        for (int j = 1; j < shape.height - 1; ++j)
            DrawSpriteScreen(
                selected ? Sprite::get("spr_ButtonCenterSelected") : Sprite::get("spr_ButtonCenter"),
                (shape.x + i - shape.width / 2) * TILE_DIMENSIONS,
                (shape.y + j - shape.height / 2) * TILE_DIMENSIONS);

    for (int i = 1; i < shape.height - 1; ++i)
    {
        DrawSpriteScreen(
            selected ? Sprite::get("spr_ButtonLeftSelected") : Sprite::get("spr_ButtonLeft"),
            (shape.x - shape.width / 2) * TILE_DIMENSIONS,
            (shape.y + i - shape.height / 2) * TILE_DIMENSIONS);

        DrawSpriteScreen(
            selected ? Sprite::get("spr_ButtonLeftSelected") : Sprite::get("spr_ButtonLeft"),
            (shape.x + shape.width / 2 - 1) * TILE_DIMENSIONS,
            (shape.y + i - shape.height / 2) * TILE_DIMENSIONS,
            true);
    }

    for (int i = 1; i < shape.width - 1; ++i)
    {
        DrawSpriteScreen(
            selected ? Sprite::get("spr_ButtonTopSelected") : Sprite::get("spr_ButtonTop"),
            (shape.x + i - shape.width / 2) * TILE_DIMENSIONS,
            (shape.y - shape.height / 2) * TILE_DIMENSIONS);

        DrawSpriteScreen(
            selected ? Sprite::get("spr_ButtonBottomSelected") : Sprite::get("spr_ButtonBottom"),
            (shape.x + i - shape.width / 2) * TILE_DIMENSIONS,
            (shape.y + shape.height / 2 - 1) * TILE_DIMENSIONS);
    }
    
    DrawSpriteScreen(
        selected ? Sprite::get("spr_ButtonTopLeftSelected") : Sprite::get("spr_ButtonTopLeft"),
        (shape.x - shape.width / 2) * TILE_DIMENSIONS,
        (shape.y - shape.height / 2) * TILE_DIMENSIONS);

    DrawSpriteScreen(
        selected ? Sprite::get("spr_ButtonBottomLeftSelected") : Sprite::get("spr_ButtonBottomLeft"),
        (shape.x - shape.width / 2) * TILE_DIMENSIONS,
        (shape.y + shape.height / 2 - 1) * TILE_DIMENSIONS);

    DrawSpriteScreen(
        selected ? Sprite::get("spr_ButtonTopLeftSelected") : Sprite::get("spr_ButtonTopLeft"),
        (shape.x + shape.width / 2 - 1) * TILE_DIMENSIONS,
        (shape.y - shape.height / 2) * TILE_DIMENSIONS,
        true);

    DrawSpriteScreen(
        selected ? Sprite::get("spr_ButtonBottomLeftSelected") : Sprite::get("spr_ButtonBottomLeft"),
        (shape.x + shape.width / 2 - 1) * TILE_DIMENSIONS,
        (shape.y + shape.height / 2 - 1) * TILE_DIMENSIONS,
        true);
    
    DrawText(label.c_str(), (shape.x * TILE_DIMENSIONS * ZOOM - MeasureText(label.c_str(), fontSize * ZOOM) / 2), (shape.y * TILE_DIMENSIONS - fontSize / 2) * ZOOM, fontSize * ZOOM, WHITE);
}
