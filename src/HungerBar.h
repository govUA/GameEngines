#ifndef MOVE_HUNGERBAR_H
#define MOVE_HUNGERBAR_H
#include <SDL.h>
#include <SDL_ttf.h>

class HungerBar {
public:
    HungerBar(SDL_Renderer *renderer, int x, int y, int width, int height);

    ~HungerBar();

    void Render(SDL_Renderer *renderer, float percentage);

private:
    SDL_Rect bgRect;
    SDL_Rect maxDimensions;
    TTF_Font *font;
    SDL_Texture *labelTexture;
    SDL_Rect labelRect;

    void CreateLabel(SDL_Renderer *renderer);
};
#endif
