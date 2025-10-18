#include "Timer.h"

Timer::Timer() {
    lastTick = SDL_GetPerformanceCounter();
    freq = static_cast<double>(SDL_GetPerformanceFrequency());
}

float Timer::GetDeltaTime() {
    Uint64 current = SDL_GetPerformanceCounter();
    float delta = static_cast<float>((current - lastTick) / freq);
    lastTick = current;
    return delta;
}
