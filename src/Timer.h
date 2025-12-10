#include <SDL2/SDL.h>

#ifndef MOVE_TIMER_H
#define MOVE_TIMER_H

#endif

class Timer {
    Uint64 lastTick;
    double freq;
public:
    Timer();

    float GetDeltaTime();
};
