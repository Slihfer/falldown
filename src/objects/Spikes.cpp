#include "Spikes.h"

#include "core/Game.h"
#include "util/collision.h"
#include "draw/draw.h"
#include "draw/Animation.h"
#include "util/rectangle.h"
#include "util/vector.h"

Spikes::Spikes(Vector2 position) : Spikes(position.x, position.y) {}

Spikes::Spikes(float x, float y) : state(Idle), stateTime(), position{ x, y } {}

void Spikes::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    switch (state)
    {
    case Idle:
        if (stateTime.elapsed() >= COOLDOWN &&
            distance(GetRectangleCenter(Game::getPlayer().getCollider()), GetRectangleCenter(getCollider())) < ACTIVATION_DISTANCE)
            setState(Poke);
        break;
    case Poke:
        if (stateTime.elapsed() >= Animation::get("anim_SpikesPoke").getDuration())
            setState(Out);
        break;
    case Out:
        if (CheckCollisionRecs(Game::getPlayer().getCollider(), getCollider()))
            Game::getPlayer().damage(
                normalize(
                    GetRectangleBottomCenter(Game::getPlayer().getCollider())
                    - GetRectangleBottomCenter(getCollider()))
                * KNOCKBACK);

        if (stateTime.elapsed() >= OUT_TIME)
            setState(Retract);
        break;
    case Retract:
        if (stateTime.elapsed() >= Animation::get("anim_SpikesRetract").getDuration())
            setState(Idle);
        break;
    }
}

void Spikes::draw()
{
    switch (state)
    {
    case Idle: DrawSpriteWorld(Sprite::get("spr_SpikesIdle"), position); break;
    case Poke: DrawSpriteWorld(Animation::get("anim_SpikesPoke").getCurrentSprite(stateTime.elapsed()), position); break;
    case Out: DrawSpriteWorld(Sprite::get("spr_SpikesOut"), position); break;
    case Retract: DrawSpriteWorld(Animation::get("anim_SpikesRetract").getCurrentSprite(stateTime.elapsed()), position); break;
    }
}

void Spikes::destroy()
{
    Game::flagDestruction();
}

void Spikes::setState(State newState)
{
    if (state != newState)
    {
        state = newState;
        stateTime.start();
    }
}

Rectangle Spikes::getCollider()
{
    return AssembleCollider(position, COLLIDER);
}
