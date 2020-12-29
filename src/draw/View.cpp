#include "View.h"

#include "core/Game.h"
#include "core/constants.h"

View::View() : y(0), scrollSpeed(MIN_SCROLL_SPEED) {}

void View::update()
{
    scrollSpeed = std::min(MAX_SCROLL_SPEED, scrollSpeed + SCROLL_ACCELERATION * Game::delta());
    y = std::max(y + Game::delta() * scrollSpeed * TILE_DIMENSIONS, Game::getPlayer().y - VIEW_MAX_PLAYER_DISTANCE);
}

float View::getY()
{
    return y;
}
