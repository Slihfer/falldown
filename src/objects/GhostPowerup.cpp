#include "GhostPowerup.h"

#include "core/Game.h"
#include "util/collision.h"
#include "draw/draw.h"
#include "draw/Animation.h"

GhostPowerup::GhostPowerup(Vector2 position) :
    PositionalObject(position),
    StateObject(State::Spawn),
    ColliderObject(COLLIDER),
    DestructibleObject() {}

GhostPowerup::GhostPowerup(float x, float y) : GhostPowerup(Vector2{ x, y }) {}

void GhostPowerup::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    switch (getState())
    {
    case State::Spawn:
        if (getStateTime().elapsed() >= Animation::get("anim_GhostPowerupSpawn").getDuration())
            setState(State::Turn);
    case State::Turn:
        if (Player& player = Game::getPlayer(); CheckCollisionRecs(player.getCollider(), getCollider()))
        {
            player.ghostPowerup();
            setState(State::Dissipate);
        }
        break;
    case State::Dissipate:
        if (getStateTime().elapsed() >= Animation::get("anim_GhostPowerupDissipate").getDuration())
            destroy();
    }
}

void GhostPowerup::draw()
{
    switch (getState())
    {
    case State::Spawn: DrawSpriteWorld(Animation::get("anim_GhostPowerupSpawn").getCurrentSprite(getStateTime().elapsed()), position, false, BLEND_ADDITIVE); break;
    case State::Turn: DrawSpriteWorld(Animation::get("anim_GhostPowerupIdle").getCurrentSprite(getStateTime().elapsed(), true), position, false, BLEND_ADDITIVE); break;
    case State::Dissipate: DrawSpriteWorld(Animation::get("anim_GhostPowerupDissipate").getCurrentSprite(getStateTime().elapsed()), position, false, BLEND_ADDITIVE); break;
    }
}