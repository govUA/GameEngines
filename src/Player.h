#include <vector>
#include "InputHandler.h"
#include "interfaces/IUpdatable.h"
#include "Obstacle.h"

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
public:
    Player(int x, int y, int w, int h, float spd, int winW, int winH);

    void ApplyInput(bool up, bool down, bool left, bool right, float dt);

    void Update(float dt) override;

    void Render(SDL_Renderer *renderer, bool textureMode) override;

    bool CollidesWith(const SDL_Rect &r);

    void SetObstacles(const std::vector<Obstacle *> *obs) {
        obstacles = obs;
    }

    void SetTexture(SDL_Texture *tex) { playerTexture = tex; }
};
