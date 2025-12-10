#include <vector>
#include "InputHandler.h"
#include "interfaces/IUpdatable.h"
#include "Obstacle.h"
#include "CollisionSystem.h"

#ifndef MOVE_PLAYER_H
#define MOVE_PLAYER_H

#endif

class Player : public IUpdatable, public IRenderable {
    float x, y;
    int w, h;
    float speed;
    float vx, vy;
    float friction;
    int windowWidth, windowHeight;
    const std::vector<Obstacle *> *obstacles = nullptr;
    SDL_Texture *playerTexture = nullptr;

    float maxHunger = 100.0f;
    float currentHunger = 100.0f;
    bool isDead = false;

public:
    Player(int x, int y, int w, int h, float spd, int winW, int winH);

    void ApplyInput(bool up, bool down, bool left, bool right, float dt);

    void Update(float dt) override;

    void Render(SDL_Renderer *renderer, bool textureMode) override;

    void Eat(float dt) {
        currentHunger = std::ranges::min(maxHunger, currentHunger + 20.0f * dt);
    }

    float GetHungerPercent() const {
        return currentHunger / maxHunger;
    }

    bool IsDead() const { return isDead; }

    Circle GetCircleCollider() const {
        return Circle{x + w / 2.0f, y + h / 2.0f, w / 2.0f};
    }

    AABB GetAABBCollider() const {
        return AABB{x, y, (float) w, (float) h};
    }

    void SetObstacles(const std::vector<Obstacle *> *obs) {
        obstacles = obs;
    }

    void SetTexture(SDL_Texture *tex) { playerTexture = tex; }
};
