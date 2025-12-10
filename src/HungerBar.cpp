#include "HungerBar.h"
#include <iostream>

HungerBar::HungerBar(SDL_Renderer *renderer, int x, int y, int width, int height) {
    maxDimensions = {x, y, width, height};
    bgRect = maxDimensions;

    font = TTF_OpenFont("../assets/fonts/tahoma.ttf", 16);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    CreateLabel(renderer);
}

HungerBar::~HungerBar() {
    if (labelTexture) {
        SDL_DestroyTexture(labelTexture);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}

void HungerBar::CreateLabel(SDL_Renderer *renderer) {
    if (!font) return;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, "Hunger", white);

    if (surface) {
        labelTexture = SDL_CreateTextureFromSurface(renderer, surface);

        labelRect.x = maxDimensions.x;
        labelRect.y = maxDimensions.y - surface->h - 2;
        labelRect.w = surface->w;
        labelRect.h = surface->h;

        SDL_FreeSurface(surface);
    }
}

void HungerBar::Render(SDL_Renderer *r, float percentage) {
    if (labelTexture) {
        SDL_RenderCopy(r, labelTexture, nullptr, &labelRect);
    }

    SDL_SetRenderDrawColor(r, 50, 50, 50, 255);
    SDL_RenderFillRect(r, &bgRect);

    if (percentage < 0.0f) percentage = 0.0f;
    if (percentage > 1.0f) percentage = 1.0f;

    int padding = 2;
    int actualWidth = static_cast<int>((maxDimensions.w - (padding * 2)) * percentage);

    SDL_Rect fgBar = {
        maxDimensions.x + padding,
        maxDimensions.y + padding,
        actualWidth,
        maxDimensions.h - (padding * 2)
    };

    if (percentage > 0.5f) {
        SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    } else if (percentage > 0.25f) {
        SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
    } else {
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    }

    SDL_RenderFillRect(r, &fgBar);
}
