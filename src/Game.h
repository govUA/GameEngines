#include "Renderer.h"
#include "Timer.h"
#include "Player.h"

#ifndef ASSIGNMENT1_GAME_H
#define ASSIGNMENT1_GAME_H

#endif

class Game {
private:
    bool running = false;
    bool paused = false;
    Renderer renderer;
    InputHandler input;
    Timer timer;
    Player player;

public:
    Game();

    void Run();
};
