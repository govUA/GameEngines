#include "InputHandler.h"

InputState InputHandler::PollEvents() {
    InputState state;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state.quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    state.quit = true;
                    break;
                case SDLK_p:
                    state.pausePressed = true;
                    break;
                case SDLK_r:
                    state.toggleRenderMode = true;
                    break;
                case SDLK_RETURN:
                    state.restartPressed = true;
                    break;
                default:
                    break;
            }
        }
    }

    int numKeys;
    const Uint8 *kb = SDL_GetKeyboardState(&numKeys);
    state.up = kb[SDL_SCANCODE_UP] || kb[SDL_SCANCODE_W];
    state.down = kb[SDL_SCANCODE_DOWN] || kb[SDL_SCANCODE_S];
    state.left = kb[SDL_SCANCODE_LEFT] || kb[SDL_SCANCODE_A];
    state.right = kb[SDL_SCANCODE_RIGHT] || kb[SDL_SCANCODE_D];

    return state;
}
