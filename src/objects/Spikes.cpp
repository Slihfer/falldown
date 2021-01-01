#include "Spikes.h"

#include "core/Game.h"
#include "util/collision.h"
#include "draw/draw.h"
#include "draw/Animation.h"
#include "util/rectangle.h"
#include "util/vector.h"

Spikes::Spikes(Vector2 position) :
    PositionalObject(position),
    ColliderObject(COLLIDER),
    StateObject(State::Idle),
    DestructibleObject(),
    VoidDestructibleObject() {}

Spikes::Spikes(float x, float y) : Spikes(Vector2{ x, y }) {}

void Spikes::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    handleVoidAuraCollisions();

    switch (getState())
    {
    case State::Idle:
        if (getStateTime().elapsed() >= COOLDOWN &&
            distance(GetRectangleCenter(Game::getPlayer().getCollider()), GetRectangleCenter(getCollider())) < ACTIVATION_DISTANCE)
            setState(State::Poke);
        break;
    case State::Poke:
        if (getStateTime().elapsed() >= Animation::get("anim_SpikesPoke").getDuration())
            setState(State::Out);
        break;
    case State::Out:
    {
        Player& player = Game::getPlayer();
        if (CheckCollisionRecs(player.getCollider(), getCollider()))
            player.damage(KNOCKBACK * Vector2{ GetRectangleCenter(player.getCollider()).x < GetRectangleCenter(getCollider()).x ? -1.0f : 1.0f, 1.0f }, HIT_STUN);

        if (getStateTime().elapsed() >= OUT_TIME)
            setState(State::Retract);
        break;
    }
    case State::Retract:
        if (getStateTime().elapsed() >= Animation::get("anim_SpikesRetract").getDuration())
            setState(State::Idle);
        break;
    }
}

void Spikes::draw()
{
    switch (getState())
    {
    case State::Idle: DrawSpriteWorld(Sprite::get("spr_SpikesIdle"), position); break;
    case State::Poke: DrawSpriteWorld(Animation::get("anim_SpikesPoke").getCurrentSprite(getStateTime().elapsed()), position); break;
    case State::Out: DrawSpriteWorld(Sprite::get("spr_SpikesOut"), position); break;
    case State::Retract: DrawSpriteWorld(Animation::get("anim_SpikesRetract").getCurrentSprite(getStateTime().elapsed()), position); break;
    }
}