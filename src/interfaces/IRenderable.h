#include <SDL2/SDL.h>

#ifndef ASSIGNMENT1_IRENDERABLE_H
#define ASSIGNMENT1_IRENDERABLE_H

#endif

class IRenderable {
public:
    virtual void Render(SDL_Renderer *renderer) = 0;

    virtual ~IRenderable() = default;
};
