#include "Player.h"
#include <algorithm>
#include <iostream>

Player::Player(int x, int y, int w, int h, float spd, int winW, int winH)
    : x(static_cast<float>(x)), y(static_cast<float>(y)),
      w(w), h(h),
      speed(spd),
      vx(0.0f), vy(0.0f),
      friction(6.0f),
      windowWidth(winW), windowHeight(winH) {
}

void Player::Eat(float dt) {
    if (isDead) return;

    currentHunger = std::ranges::min(maxHunger, currentHunger + 20.0f * dt);

    if (texEat) {
        currentTexture = texEat;
        eatTimer = 0.5f;
    }
}

void Player::ApplyInput(bool up, bool down, bool left, bool right, float dt) {
    if (isDead) return;

    const float accel = speed;

    if (up) vy -= accel * dt;
    if (down) vy += accel * dt;
    if (left) vx -= accel * dt;
    if (right) vx += accel * dt;

    const float maxSpeed = 1024.0f;
    vx = std::clamp(vx, -maxSpeed, maxSpeed);
    vy = std::clamp(vy, -maxSpeed, maxSpeed);
}

void Player::Update(float dt) {
    if (!isDead) {
        if (eatTimer > 0) {
            eatTimer -= dt;
            if (eatTimer <= 0) {
                currentTexture = texNormal;
            }
        }
    }

    if (isDead) return;

    currentHunger -= 5.0f * dt;
    if (currentHunger <= 0.0f) {
        currentHunger = 0.0f;
        isDead = true;

        if (texDead) currentTexture = texDead;

        std::cout << "GAME OVER: You starved to death!" << std::endl;
    }

    x += vx * dt;
    y += vy * dt;

    vx -= vx * std::min(friction * dt, 1.0f);
    vy -= vy * std::min(friction * dt, 1.0f);

    if (obstacles) {
        Circle myCircle = GetCircleCollider();
        AABB myBox = GetAABBCollider();

        for (auto *o: *obstacles) {
            SDL_Rect r = o->GetRect();
            AABB obsBox = {(float) r.x, (float) r.y, (float) r.w, (float) r.h};

            if (CollisionSystem::BroadPhaseCheck(myBox, obsBox)) {
                CollisionResult res = CollisionSystem::NarrowPhaseCheck(myCircle, obsBox);

                if (res.isColliding) {
                    CollisionSystem::ResolveCollision(x, y, res);

                    if (res.normalX != 0) vx = 0;
                    if (res.normalY != 0) vy = 0;

                    if (o->isTrigger) {
                        o->OnCollision();
                        Eat(dt);
                    }
                }
            }
        }
    }

    if (x < 0) {
        x = 0;
        vx = 0;
    }
    if (y < 0) {
        y = 0;
        vy = 0;
    }
    if (x + w > windowWidth) {
        x = windowWidth - w;
        vx = 0;
    }
    if (y + h > windowHeight) {
        y = windowHeight - h;
        vy = 0;
    }
}

void Player::Render(SDL_Renderer *renderer, bool textureMode) {
    SDL_Rect drawRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        w,
        h
    };
    if (!textureMode || currentTexture == nullptr) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
        SDL_RenderFillRect(renderer, &drawRect);
    } else {
        SDL_RenderCopy(renderer, currentTexture, nullptr, &drawRect);
    }
}
