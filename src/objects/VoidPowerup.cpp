#include "VoidPowerup.h"

#include "core/Game.h"
#include "util/collision.h"
#include "draw/draw.h"
#include "draw/Animation.h"

VoidPowerup::VoidPowerup(Vector2 position) :
    PositionalObject(position),
    StateObject(State::Spawn),
    ColliderObject(COLLIDER),
    DestructibleObject() {}

VoidPowerup::VoidPowerup(float x, float y) : VoidPowerup(Vector2{ x, y }) {}

void VoidPowerup::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    switch (getState())
    {
    case State::Spawn:
        if (getStateTime().elapsed() >= Animation::get("anim_VoidPowerupSpawn").getDuration())
            setState(State::Idle);
    case State::Idle:
        if (Player& player = Game::getPlayer(); CheckCollisionRecs(player.getCollider(), getCollider()))
        {
            player.voidPowerup();
            setState(State::Dissipate);
        }
        break;
    case State::Dissipate:
        if (getStateTime().elapsed() >= Animation::get("anim_VoidPowerupDissipate").getDuration())
            destroy();
    }
}

void VoidPowerup::draw()
{
    switch (getState())
    {
    case State::Spawn:
        DrawSpriteWorld(Animation::get("anim_VoidPowerupSpawnBG").getCurrentSprite(getStateTime().elapsed()), position, false, BLEND_ADDITIVE);
        DrawSpriteWorld(Animation::get("anim_VoidPowerupSpawn").getCurrentSprite(getStateTime().elapsed()), position);
        break;
    case State::Idle:
        DrawSpriteWorld(Animation::get("anim_VoidPowerupIdleBG").getCurrentSprite(getStateTime().elapsed(), true), position, false, BLEND_ADDITIVE);
        DrawSpriteWorld(Animation::get("anim_VoidPowerupIdle").getCurrentSprite(getStateTime().elapsed(), true), position);
        break;
    case State::Dissipate:
        DrawSpriteWorld(Animation::get("anim_VoidPowerupDissipateBG").getCurrentSprite(getStateTime().elapsed()), position, false, BLEND_ADDITIVE);
        DrawSpriteWorld(Animation::get("anim_VoidPowerupDissipate").getCurrentSprite(getStateTime().elapsed()), position);
        break;
    }
}