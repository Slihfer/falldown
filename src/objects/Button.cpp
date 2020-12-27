#include "Button.h"

#include "core/Game.h"

Button::Button(
    Rectangle shape,
    const std::string& label,
    int fontSize,
    const std::function<void()>& selectAction,
    bool selected) :
    shape(shape),
    label(label),
    fontSize(fontSize),
    selectAction(selectAction),
    selected(selected) {}

void Button::update()
{
    if (selected && IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_K))
        selectAction();
}

void Button::draw()
{
    for (int i = 1; i < shape.width - 1; ++i)
        for (int j = 1; j < shape.height - 1; ++j)
            Game::getView().drawSpriteScreen(
                selected ? Sprite::get("spr_ButtonCenterSelected") : Sprite::get("spr_ButtonCenter"),
                ((shape.x) + i * TILE_DIMENSIONS - shape.width / 2) * ZOOM,
                ((shape.y) + j * TILE_DIMENSIONS - shape.height / 2) * ZOOM);
    /*
    Game::getView().drawSpriteScreen(
        selected ? Sprite::get("spr_ButtonCenterSelected") : Sprite::get("spr_ButtonCenter"),
        (shape.x * TILE_DIMENSIONS - shape.width / 2) * ZOOM,
        (shape.y * TILE_DIMENSIONS - shape.height / 2) * ZOOM);
    */
    DrawText(label.c_str(), (shape.x * TILE_DIMENSIONS - MeasureText(label.c_str(), fontSize) / 2) * ZOOM, (shape.y * TILE_DIMENSIONS - fontSize / 2) * ZOOM, fontSize, WHITE);
}
