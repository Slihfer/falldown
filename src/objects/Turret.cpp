#include "Turret.h"

#include "core/Game.h"
#include "draw/Animation.h"
#include "util/rectangle.h"
#include "draw/draw.h"

Turret::Turret(Vector2 position, bool looksLeft) :
    PositionalObject(position),
    DirectionalObject(looksLeft),
    StateObject(State::Idle),
    ColliderObject(COLLIDER),
    DestructibleObject(),
    VoidDestructibleObject(),
    collider{ 0, y + COLLIDER_OFFSET, LEVEL_WIDTH, COLLIDER_HEIGHT } {}

Turret::Turret(float x, float y, bool looksLeft) : Turret({ x, y }, looksLeft) {}

void Turret::update()
{
    if (Game::getLevel().isAbove(y))
        destroy();

    handleVoidAuraCollisions();

    switch (getState())
    {
    case State::Idle:
        if (abs(Game::getPlayer().y - y) < ACTIVATION_DISTANCE)
            setState(State::Charge);

        break;
    case State::Charge:
        if (getStateTime().elapsed() >= Animation::get("anim_TurretBeamCharge").getDuration())
            setState(State::Shoot);

        break;
    case State::Shoot:
    {
        Player& player = Game::getPlayer();
        if (!player.hasVoidPowerup() && CheckCollisionRecs(player.getCollider(), collider))
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
            DrawSpriteWorld(Sprite::get("spr_TurretCharge"), position, looksLeft);
            DrawSpriteWorld(Animation::get("anim_TurretBeamCharge").getCurrentSprite(getStateTime().elapsed()), position, looksLeft, BLEND_ADDITIVE);

            break;
        case State::Shoot:
        {
            DrawSpriteWorld(Sprite::get("spr_TurretShoot"), position, looksLeft);

            const Animation& beamCenterAnim = Animation::get("anim_TurretBeamCenter");
            Player& player = Game::getPlayer();

            if (!player.hasVoidPowerup() || !CheckCollisionCircleRec(GetRectangleCenter(player.getCollider()), Player::VOID_AURA_RADIUS, { x, y + COLLIDER_OFFSET, TILE_DIMENSIONS, COLLIDER_HEIGHT }))
                DrawSpriteWorld(Animation::get("anim_TurretBeamStart").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft, BLEND_ADDITIVE);

            for (int i = 1; i < TILES_X - 1; ++i)
            {
                if (player.hasVoidPowerup() && CheckCollisionCircleRec(GetRectangleCenter(player.getCollider()), Player::VOID_AURA_RADIUS, { static_cast<float>((looksLeft ? TILES_X - 1 - i : i) * TILE_DIMENSIONS), y + COLLIDER_OFFSET, TILE_DIMENSIONS, COLLIDER_HEIGHT }))
                    goto skipBeam;

                DrawSpriteWorld(beamCenterAnim.getCurrentSprite(getStateTime().elapsed() + i * 0.05f, true), { static_cast<float>((looksLeft ? TILES_X - 1 - i : i) * TILE_DIMENSIONS), y }, looksLeft, BLEND_ADDITIVE);
            }

            if (!player.hasVoidPowerup() || !CheckCollisionCircleRec(GetRectangleCenter(player.getCollider()), Player::VOID_AURA_RADIUS, { LEVEL_WIDTH - TILE_DIMENSIONS - x, y + COLLIDER_OFFSET, TILE_DIMENSIONS, COLLIDER_HEIGHT }))
                DrawSpriteWorld(Animation::get("anim_TurretBeamEnd").getCurrentSprite(getStateTime().elapsed(), true), { LEVEL_WIDTH - TILE_DIMENSIONS - x, y }, looksLeft, BLEND_ADDITIVE);

        skipBeam:
            break;
        }
        case State::Retract:
            DrawSpriteWorld(Animation::get("anim_TurretRetract").getCurrentSprite(getStateTime().elapsed()), position, looksLeft);

            break;
    }
}
