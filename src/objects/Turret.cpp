#include "Turret.h"

#include "core/Game.h"
#include "draw/Animation.h"
#include "util/rectangle.h"
#include "draw/draw.h"

Turret::Turret(Vector2 position, bool looksLeft) :
    PositionalObject(position),
    DirectionalObject(looksLeft),
    StateObject(State::Idle),
    DestructibleObject(),
    collider{ 0, y + COLLIDER_OFFSET, LEVEL_WIDTH, COLLIDER_HEIGHT } {}

Turret::Turret(float x, float y, bool looksLeft) : Turret({ x, y }, looksLeft) {}

void Turret::update()
{
    switch (getState())
    {
    case State::Idle:
        if (abs(Game::getPlayer().y - y) < ACTIVATION_DISTANCE)
            setState(State::Charge);

        break;
    case State::Charge:
        if (getStateTime().elapsed() >= CHARGE_TIME)
            setState(State::Shoot);

        break;
    case State::Shoot:
    {
        Player& player = Game::getPlayer();
        if (CheckCollisionRecs(player.getCollider(), collider))
            player.damage(KNOCKBACK, HIT_STUN);

        if (getStateTime().elapsed() >= SHOOT_TIME)
            setState(State::Retract);

        break;
    }
    case State::Retract:
        if (getStateTime().elapsed() >= Animation::get("anim_TurretRetract").getDuration())
            setState(State::Idle);

        break;
    }
}

void Turret::draw()
{
    switch (getState())
    {
        case State::Idle:
            DrawSpriteWorld(Sprite::get("spr_TurretIdle"), position, looksLeft);

            break;
        case State::Charge:
            DrawSpriteWorld(Sprite::get("spr_TurretIdle"), position, looksLeft);
            DrawSpriteWorld(Animation::get("anim_TurretBeamCharge").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft, true);

            break;
        case State::Shoot:
        {
            DrawSpriteWorld(Sprite::get("spr_TurretShoot"), position, looksLeft);

            const Animation& beamCenterAnim = Animation::get("anim_TurretBeamCenter");

            for (int i = 1; i < TILES_X - 1; ++i)
                DrawSpriteWorld(beamCenterAnim.getCurrentSprite(getStateTime().elapsed() + (looksLeft ? ((TILES_X - i) * 0.05f) : (i * 0.05f)), true), { static_cast<float>(i * TILE_DIMENSIONS), y }, looksLeft, true);

            DrawSpriteWorld(Animation::get("anim_TurretBeamStart").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft, true);
            DrawSpriteWorld(Animation::get("anim_TurretBeamEnd").getCurrentSprite(getStateTime().elapsed(), true), { LEVEL_WIDTH - TILE_DIMENSIONS - x, y }, looksLeft, true);

            break;
        }
        case State::Retract:
            DrawSpriteWorld(Animation::get("anim_TurretRetract").getCurrentSprite(getStateTime().elapsed()), position, looksLeft);

            break;
    }
}
