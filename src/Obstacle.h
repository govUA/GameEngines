#ifndef ASSIGNMENT1_OBSTACLE_H
#define ASSIGNMENT1_OBSTACLE_H

#include <SDL2/SDL.h>
#include "interfaces/IRenderable.h"

class Obstacle : public IRenderable {
    SDL_Texture *obstacleTexture = nullptr;
public:
    int x, y, w, h;

    Obstacle(int x, int y, int w, int h)
            : x(x), y(y), w(w), h(h) {}

    SDL_Rect GetRect() const {
        return SDL_Rect{x, y, w, h};
    }

    void Render(SDL_Renderer *renderer, bool textureMode) override {
        SDL_Rect r = GetRect();
        if (!textureMode || obstacleTexture == nullptr) {
            SDL_SetRenderDrawColor(renderer, 160, 40, 40, 255);
            SDL_RenderFillRect(renderer, &r);
        } else {
            SDL_RenderCopy(renderer, obstacleTexture, nullptr, &r);
        }
    }

    void SetTexture(SDL_Texture *tex) { obstacleTexture = tex; }
};

#endif
