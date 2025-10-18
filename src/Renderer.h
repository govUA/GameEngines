#include <SDL2/SDL.h>
#include <string>

#ifndef ASSIGNMENT1_RENDERER_H
#define ASSIGNMENT1_RENDERER_H

#endif

class Renderer {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
public:
    Renderer(const std::string &title, int width, int height);

    ~Renderer();

    void Clear();

    void Present();

    SDL_Renderer *GetSDLRenderer() const { return renderer; };
};
