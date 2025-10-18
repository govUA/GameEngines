#include "Game.h"

Game::Game()
        : renderer("Move", 800, 600),
          player(400, 300, 50, 50, 1024.0f, 800, 600) {}

void Game::Run() {
    running = true;
    while (running) {
        float dt = timer.GetDeltaTime();

        InputState in = input.PollEvents();

        if (in.quit) {
            running = false;
            continue;
        }

        if (in.pausePressed) {
            paused = !paused;
        }

        if (!paused) {
            player.ApplyInput(in.up, in.down, in.left, in.right, dt);
            player.Update(dt);
        }

        renderer.Clear();
        player.Render(renderer.GetSDLRenderer());
        renderer.Present();
    }
}
