#include "Player.h"

#include <algorithm>

#include "core/Game.h"
#include "core/input.h"
#include "core/constants.h"
#include "draw/Animation.h"
#include "draw/draw.h"
#include "util/rectangle.h"
#include "screens/MenuBackground.h"
#include "sound/SoundEffect.h"

//TODO make time checking more general

Player::Player() :
    PositionalObject((LEVEL_WIDTH - TILE_DIMENSIONS) / 2, LEVEL_HEIGHT - VIEW_MAX_PLAYER_DISTANCE),
    KineticObject(),
    DirectionalObject(),
    ColliderObject(COLLIDER),
    StateObject(State::Air) {}

void Player::die()
{
    Game::signalGameOver();
}

void Player::update()
{
    if (Game::getLevel().isAbove(y))
        die();

    if (IsInputInactive<InputAction::Jump>())
        jumpBoostEndTime.end();

    if (isState(State::Air) && IsInputStarted<InputAction::Jump>())
        jumpBuffer.start();

    if (hitStunTime.isExpired())
    {
        if (IsInputActive<InputAction::Left>() && velocity.x > 0 || IsInputActive<InputAction::Right>() && velocity.x < 0)
        {
            turnTime.start();
            velocity.x = 0;
        }

        if (turnTime.isExpired())
        {
            velocity.x += ACCELERATION * Game::delta() * (IsInputActive<InputAction::Right>() - IsInputActive<InputAction::Left>());
            looksLeft = IsInputActive<InputAction::Left>() ^ IsInputActive<InputAction::Right>() ? IsInputActive<InputAction::Left>() : looksLeft;
        }

        if ((getState() != State::Air ||
            coyoteTime.isOngoing()) &&
            (IsInputStarted<InputAction::Jump>() ||
                (jumpBuffer.isOngoing()) && IsInputActive<InputAction::Jump>()))
        {
            velocity.y = JUMP_SPEED;
            coyoteTime.end();
            jumpBuffer.end();
            jumpBoostStartTime.start();
            jumpBoostEndTime.start();
            setState(State::Air);

            SoundEffect::playMulti("sfx_Jump");
        }
        else if (velocity.y < 0 && (jumpBoostStartTime.isOngoing() || (IsInputActive<InputAction::Jump>() && jumpBoostEndTime.isOngoing())))
        {
            velocity.y = JUMP_SPEED;
        }
    }

    velocity.y += GRAVITY * Game::delta();
    

    if (abs(velocity.x) < SPEED_THRESHOLD)
        velocity.x = 0;

    applyVelocity();

    if (!isState(State::Air) || (hitStunTime.isExpired() && (IsInputActive<InputAction::Left>() || IsInputActive<InputAction::Right>())))
        velocity *= 1.0f - FRICTION * Game::delta();
    velocity *= 1.0f - DRAG * Game::delta();

    if (Game::getLevel().handleCollision(position, COLLIDER, velocity).y < 0)
    {
        coyoteTime.start();

        if (velocity.x == 0)
            setStateIfChanged(State::Idle);
        else
            setStateIfChanged(State::Walk);
    }
    else
    {
        setStateIfChanged(State::Air);
    }
}

void Player::draw()
{
    for (int i = 0; i < health; ++i)
        DrawSpriteScreen(Sprite::get("spr_PlayerLife"), i * TILE_DIMENSIONS + 4, 4);

    DrawUIBox({ 2, 1, 4.0f, 2 });

    if (hitStunTime.isOngoing())
        DrawSpriteWorld(Sprite::get("spr_PlayerHurt"), position, looksLeft);
    else
        switch (getState())
        {
        case State::Idle:
            DrawSpriteWorld(Animation::get("anim_PlayerIdle").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft);
            break;
        case State::Walk:
            DrawSpriteWorld(Animation::get("anim_PlayerWalk").getCurrentSprite(getStateTime().elapsed(), true), position, looksLeft);
            break;
        case State::Air:
            if (velocity.y <= SLOW_JUMP_THRESHOLD)
                DrawSpriteWorld(Sprite::get("spr_PlayerFastJump"), position, looksLeft);
            else if (velocity.y <= JUMP_HOVER_THRESHOLD) //velocity.y < PLAYER_FALL_HOVER_THRESHOLD && velocity.y > PLAYER_JUMP_HOVER_THRESHOLD)
                DrawSpriteWorld(Sprite::get("spr_PlayerSlowJump"), position, looksLeft);
            else if (velocity.y <= FALL_HOVER_THRESHOLD)
                DrawSpriteWorld(Sprite::get("spr_PlayerHover"), position, looksLeft);
            else
                DrawSpriteWorld(Sprite::get("spr_PlayerFall"), position, looksLeft);
            break;
        }

    if (invulnerabilityTime.isOngoing())
        DrawSpriteWorld(Sprite::get("spr_GhostAura"), position - HALF_TILE_DIMENSIONS, false, BLEND_ADDITIVE);

    if (voidPowerupTime.isOngoing())
    {
        DrawSpriteWorld(
            voidPowerupTime.elapsed() < Animation::get("anim_VoidAuraSpawn").getDuration() ?
            Animation::get("anim_VoidAuraSpawn").getCurrentSprite(voidPowerupTime.elapsed()) : (
            voidPowerupTime.elapsed() >= voidPowerupTime.getDuration() - Animation::get("anim_VoidAuraDissipate").getDuration() ?
            Animation::get("anim_VoidAuraDissipate").getCurrentSprite(Animation::get("anim_VoidAuraDissipate").getDuration() - voidPowerupTime.remaining()) :
            Sprite::get("spr_VoidAura")),
            position - 16);
        DrawSpriteWorld(Animation::get("anim_VoidAuraBG").getCurrentSprite(voidPowerupTime.elapsed(), true), position - 16, false, BLEND_ADDITIVE);
    }
}

void Player::damage(Vector2 knockback, float hitStun)
{
    if (!isInvulnerable())
    {
        if (!--health)
            die();

        invulnerabilityTime.start(hitStun * 2.0f);
        hitStunTime.start(hitStun);

        velocity = knockback;

        SoundEffect::play("sfx_Hurt");
    }
}

void Player::ghostPowerup()
{
    invulnerabilityTime.start(GHOST_POWERUP_TIME);

    SoundEffect::playMulti("sfx_GhostPickup");
}

void Player::voidPowerup()
{
    voidPowerupTime.start();

    SoundEffect::playMulti("sfx_VoidPickup");
}

bool Player::isInvulnerable()
{
    return invulnerabilityTime.isOngoing();
}

bool Player::hasVoidPowerup()
{
    return voidPowerupTime.isOngoing();
}
