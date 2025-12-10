#include <SDL2/SDL_image.h>
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
    SDL_Texture *playerTexture = nullptr;
    std::vector<SDL_Texture *> obstacleTextures;

public:
    Game();

    void Run();

    ~Game() {
        SDL_DestroyTexture(playerTexture);

        for (auto *tex: obstacleTextures)
            SDL_DestroyTexture(tex);

        for (auto *o: obstacles)
            delete o;
    }

};
