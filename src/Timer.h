#include <SDL2/SDL.h>

#ifndef ASSIGNMENT1_TIMER_H
#define ASSIGNMENT1_TIMER_H

#endif

class Timer {
    Uint64 lastTick;
    double freq;
public:
    Timer();

    float GetDeltaTime();
};
