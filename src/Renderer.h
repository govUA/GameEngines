#include <SDL2/SDL.h>
#include <string>

#ifndef MOVE_RENDERER_H
#define MOVE_RENDERER_H

#endif

class Renderer {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool useTextures = false;
public:
    Renderer(const std::string &title, int width, int height);

    ~Renderer();

    void Clear();

    void Present();

    SDL_Renderer *GetSDLRenderer() const { return renderer; };

    void ToggleRenderMode() { useTextures = !useTextures; }

    bool IsTextureMode() const { return useTextures; }
};
