#include "Game.h"

Game::Game()
    : renderer("Move", 800, 600),
      player(400, 300, 20, 42, 1024.0f, 800, 600) {
    SDL_Renderer *r = renderer.GetSDLRenderer();

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    }

    gameFont = TTF_OpenFont("../assets/fonts/tahoma.ttf", 32);
    if (!gameFont) {
        std::cerr << "Failed to load game font!" << std::endl;
    }
    CreateGameOverText(r);

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

void Game::CreateGameOverText(SDL_Renderer *r) {
    if (!gameFont) return;
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *surf1 = TTF_RenderText_Blended(gameFont, "GAME OVER", red);
    if (surf1) {
        texGameOver = SDL_CreateTextureFromSurface(r, surf1);
        rectGameOver.w = surf1->w;
        rectGameOver.h = surf1->h;
        rectGameOver.x = (800 - surf1->w) / 2;
        rectGameOver.y = (600 - surf1->h) / 2 - 30;
        SDL_FreeSurface(surf1);
    }

    SDL_Surface *surf2 = TTF_RenderText_Blended(gameFont, "Press ENTER to restart", white);
    if (surf2) {
        texRestart = SDL_CreateTextureFromSurface(r, surf2);
        rectRestart.w = surf2->w;
        rectRestart.h = surf2->h;
        rectRestart.x = (800 - surf2->w) / 2;
        rectRestart.y = rectGameOver.y + rectGameOver.h + 10;
        SDL_FreeSurface(surf2);
    }

    int padding = 20;
    int totalWidth = std::max(rectGameOver.w, rectRestart.w) + (padding * 2);
    int totalHeight = (rectRestart.y + rectRestart.h) - rectGameOver.y + (padding * 2);

    rectGameOverBg.x = (800 - totalWidth) / 2;
    rectGameOverBg.y = rectGameOver.y - padding;
    rectGameOverBg.w = totalWidth;
    rectGameOverBg.h = totalHeight;
}

void Game::ResetGame() {
    player.Reset(400, 300);
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

        if (player.IsDead() && in.restartPressed) {
            ResetGame();
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

        if (player.IsDead()) {
            SDL_SetRenderDrawColor(r, 100, 100, 100, 255);
            SDL_RenderFillRect(r, &rectGameOverBg);

            SDL_SetRenderDrawColor(r, 200, 200, 200, 255);
            SDL_RenderDrawRect(r, &rectGameOverBg);

            if (texGameOver) SDL_RenderCopy(r, texGameOver, nullptr, &rectGameOver);
            if (texRestart) SDL_RenderCopy(r, texRestart, nullptr, &rectRestart);
        }

        renderer.Present();
    }
}

Game::~Game() {
    SDL_DestroyTexture(texHeroNormal);
    SDL_DestroyTexture(texHeroEat);
    SDL_DestroyTexture(texHeroDead);

    SDL_DestroyTexture(texGameOver);
    SDL_DestroyTexture(texRestart);
    if (gameFont) TTF_CloseFont(gameFont);

    for (auto *tex: obstacleTextures)
        SDL_DestroyTexture(tex);

    for (auto *o: obstacles)
        delete o;

    delete hungerBar;

    TTF_Quit();
}
