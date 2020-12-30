#include "Powerup.h"

#include "core/Game.h"
#include "util/collision.h"
#include "draw/draw.h"
#include "draw/Animation.h"

Powerup::Powerup(Vector2 position) : Powerup(position.x, position.y) {}

Powerup::Powerup(float x, float y) : state(Spawn), stateTime(), position{ x, y } {}

void Powerup::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    switch (state)
    {
    case Spawn:
        if (stateTime.elapsed() >= Animation::get("anim_PowerupSpawn").getDuration())
            setState(Idle);
    case Idle:
        if (Player& player = Game::getPlayer(); CheckCollisionRecs(player.getCollider(), getCollider()))
        {
            player.powerup();
            setState(Dissipate);
        }
        break;
    case Dissipate:
        if (stateTime.elapsed() >= Animation::get("anim_PowerupDissipate").getDuration())
            destroy();
    }
}

void Powerup::draw()
{
    switch (state)
    {
    case Spawn: DrawSpriteWorld(Animation::get("anim_PowerupSpawn").getCurrentSprite(stateTime.elapsed()), position, false, true); break;
    case Idle: DrawSpriteWorld(Animation::get("anim_PowerupIdle").getCurrentSprite(stateTime.elapsed(), true), position, false, true); break;
    case Dissipate: DrawSpriteWorld(Animation::get("anim_PowerupDissipate").getCurrentSprite(stateTime.elapsed()), position, false, true); break;
    }
}

void Powerup::destroy()
{
    Game::flagDestruction();
}

void Powerup::setState(State newState)
{
    if (state != newState)
    {
        state = newState;
        stateTime.start();
    }
}

Rectangle Powerup::getCollider()
{
    return AssembleCollider(position, COLLIDER);
}
