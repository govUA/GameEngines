#include "Game.h"

Game::Game()
        : renderer("Move", 800, 600),
          player(400, 300, 20, 42, 1024.0f, 800, 600) {
    obstacles.push_back(new Obstacle(96, 128, 205, 180));
    obstacles.push_back(new Obstacle(576, 256, 111, 127));
    obstacles.push_back(new Obstacle(448, 64, 61, 206));
    obstacles.push_back(new Obstacle(256, 384, 69, 169));
    player.SetObstacles(&obstacles);
}

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
        for (auto *o: obstacles)
            o->Render(renderer.GetSDLRenderer());
        renderer.Present();
    }
}
