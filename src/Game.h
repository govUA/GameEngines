#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include "HungerBar.h"
#include "Renderer.h"
#include "Timer.h"
#include "Player.h"

#ifndef MOVE_GAME_H
#define MOVE_GAME_H

#endif

class Game {
private:
    bool running = false;
    bool paused = false;
    Renderer renderer;
    InputHandler input;
    Timer timer;
    Player player;
    std::vector<Obstacle *> obstacles;

    SDL_Texture *texHeroNormal = nullptr;
    SDL_Texture *texHeroEat = nullptr;
    SDL_Texture *texHeroDead = nullptr;

    std::vector<SDL_Texture *> obstacleTextures;
    HungerBar *hungerBar;

public:
    Game();

    void Run();

    ~Game();
};
