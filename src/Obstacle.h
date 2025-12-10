#ifndef MOVE_OBSTACLE_H
#define MOVE_OBSTACLE_H

#include <SDL2/SDL.h>
#include <iostream>
#include "interfaces/IRenderable.h"

class Obstacle : public IRenderable {
    SDL_Texture *obstacleTexture = nullptr;

public:
    int x, y, w, h;
    bool isTrigger;

    Obstacle(int x, int y, int w, int h, bool trigger = false)
        : x(x), y(y), w(w), h(h), isTrigger(trigger) {
    }

    SDL_Rect GetRect() const {
        return SDL_Rect{x, y, w, h};
    }

    void OnCollision() {
        if (isTrigger) {
            std::cout << "[Event] Trigger Activated at (" << x << "," << y << ")!" << std::endl;
        }
    }

    void Render(SDL_Renderer *renderer, bool textureMode) override {
        SDL_Rect r = GetRect();
        if (!textureMode || obstacleTexture == nullptr) {
            if (isTrigger) SDL_SetRenderDrawColor(renderer, 40, 40, 160, 255);
            else SDL_SetRenderDrawColor(renderer, 160, 40, 40, 255);

            SDL_RenderFillRect(renderer, &r);
        } else {
            SDL_RenderCopy(renderer, obstacleTexture, nullptr, &r);
        }
    }

    void SetTexture(SDL_Texture *tex) { obstacleTexture = tex; }
};

#endif
