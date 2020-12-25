#include "Player.h"

#include <algorithm>

#include "core/Game.h"
#include "core/constants.h"

void Player::update(float t)
{
    float lastY = y;

    velocity.x = PLAYER_SPEED * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
    velocity.y += PLAYER_GRAVITY * t;

    x = std::clamp(x + t * velocity.x, -PLAYER_COLLIDER.x, static_cast<float>(LEVEL_WIDTH + PLAYER_COLLIDER.x - PLAYER_COLLIDER.width));
    y = y + t * velocity.y;

    Vector2 feetCenter = { x + HALF_TILE_DIMENSIONS, y + TILE_DIMENSIONS };

    if
    (
        (
            !(fmodf(lastY, TILE_DIMENSIONS)) ||
            static_cast<int>(lastY / TILE_DIMENSIONS) != static_cast<int>(y / TILE_DIMENSIONS)
        ) && 
        (
            Game::getLevel().collides(feetCenter.x - PLAYER_COLLIDER.width / 2, feetCenter.y) ||
            Game::getLevel().collides(feetCenter.x + PLAYER_COLLIDER.width / 2, feetCenter.y)
        )
    )
    {
        y = floor(y / TILE_DIMENSIONS) * TILE_DIMENSIONS;
        velocity.y = 0.0f;
    }
}

void Player::draw()
{
    Game::getView().drawSprite(Sprite::get("spr_Player"), position);
}
