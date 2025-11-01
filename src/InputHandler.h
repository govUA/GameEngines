#include <SDL2/SDL.h>

#ifndef ASSIGNMENT1_INPUTHANDLER_H
#define ASSIGNMENT1_INPUTHANDLER_H

#endif

struct InputState {
    bool quit = false;
    bool pausePressed = false;
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool toggleRenderMode = false;
};

class InputHandler {
public:
    InputState PollEvents();
};
