#include "View.h"

#include "core/Game.h"
#include "core/constants.h"

View::View() : y(0), scrollSpeed(2) {}

void View::update()
{
    y = std::max(y + Game::delta() * scrollSpeed * TILE_DIMENSIONS, Game::getPlayer().y - VIEW_MAX_PLAYER_DISTANCE);
}

float View::getY()
{
    return y;
}
