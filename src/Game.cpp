#include "Game.h"

Game::Game()
    : renderer("Move", 800, 600),
      player(400, 300, 20, 42, 1024.0f, 800, 600) {
    SDL_Renderer *r = renderer.GetSDLRenderer();

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    }

    hungerBar = new HungerBar(r, 20, 45, 200, 25);

    obstacles.push_back(new Obstacle(96, 128, 205, 180));
    obstacleTextures.push_back(IMG_LoadTexture(r, "../assets/gfx/building01.png"));
    obstacles.back()->SetTexture(obstacleTextures.back());

    obstacles.push_back(new Obstacle(576, 256, 111, 127, true));
    obstacleTextures.push_back(IMG_LoadTexture(r, "../assets/gfx/building02.png"));
    obstacles.back()->SetTexture(obstacleTextures.back());

    obstacles.push_back(new Obstacle(256, 384, 69, 169));
    obstacleTextures.push_back(IMG_LoadTexture(r, "../assets/gfx/building03.png"));
    obstacles.back()->SetTexture(obstacleTextures.back());

    obstacles.push_back(new Obstacle(448, 64, 61, 206));
    obstacleTextures.push_back(IMG_LoadTexture(r, "../assets/gfx/building04.png"));
    obstacles.back()->SetTexture(obstacleTextures.back());

    texHeroNormal = IMG_LoadTexture(r, "../assets/gfx/hero.png");
    texHeroEat = IMG_LoadTexture(r, "../assets/gfx/eating.png");
    texHeroDead = IMG_LoadTexture(r, "../assets/gfx/dead.png");

    player.SetNormalTexture(texHeroNormal);
    player.SetEatTexture(texHeroEat);
    player.SetDeadTexture(texHeroDead);

    player.SetObstacles(&obstacles);
}

void Game::Run() {
    running = true;
    while (running) {
        float dt = timer.GetDeltaTime();
        InputState in = input.PollEvents();

        if (in.toggleRenderMode) renderer.ToggleRenderMode();
        if (in.quit) {
            running = false;
            continue;
        }
        if (in.pausePressed) paused = !paused;

        if (!paused) {
            player.ApplyInput(in.up, in.down, in.left, in.right, dt);
            player.Update(dt);
        }

        renderer.Clear();
        SDL_Renderer *r = renderer.GetSDLRenderer();
        bool texMode = renderer.IsTextureMode();

        player.Render(r, texMode);
        for (auto *o: obstacles)
            o->Render(r, texMode);

        hungerBar->Render(r, player.GetHungerPercent());

        renderer.Present();
    }
}

Game::~Game() {
    SDL_DestroyTexture(texHeroNormal);
    SDL_DestroyTexture(texHeroEat);
    SDL_DestroyTexture(texHeroDead);

    for (auto *tex: obstacleTextures)
        SDL_DestroyTexture(tex);

    for (auto *o: obstacles)
        delete o;

    delete hungerBar;

    TTF_Quit();
}
