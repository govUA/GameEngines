#include "Player.h"
#include <algorithm>
#include <iostream>

Player::Player(int x, int y, int w, int h, float spd, int winW, int winH)
        : x(static_cast<float>(x)), y(static_cast<float>(y)),
          w(w), h(h),
          speed(spd),
          vx(0.0f), vy(0.0f),
          friction(6.0f),
          windowWidth(winW), windowHeight(winH) {}

void Player::ApplyInput(bool up, bool down, bool left, bool right, float dt) {
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
    float oldX = x;
    float oldY = y;

    x += vx * dt;
    y += vy * dt;

    vx -= vx * std::min(friction * dt, 1.0f);
    vy -= vy * std::min(friction * dt, 1.0f);

    if (obstacles) {
        for (auto *o: *obstacles) {
            if (CollidesWith(o->GetRect())) {
                x = oldX;
                y = oldY;
                vx = 0;
                vy = 0;
                break;
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
    if (!textureMode || playerTexture == nullptr) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 100, 255);
        SDL_RenderFillRect(renderer, &drawRect);
    } else {
        SDL_RenderCopy(renderer, playerTexture, nullptr, &drawRect);
    }
}

bool Player::CollidesWith(const SDL_Rect &r) {
    SDL_Rect me{(int) x, (int) y, w, h};
    return SDL_HasIntersection(&me, &r);
}
