#include <SDL2/SDL.h>

#ifndef MOVE_IRENDERABLE_H
#define MOVE_IRENDERABLE_H

#endif

class IRenderable {
public:
    virtual void Render(SDL_Renderer *renderer, bool textureMode) = 0;

    virtual ~IRenderable() = default;
};
