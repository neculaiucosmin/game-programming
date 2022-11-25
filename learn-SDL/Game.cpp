#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
        : mWindow(nullptr),
          mRenderer(nullptr),
          mIsRunning(true),
          mTicksCount(0) {}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
            "Game dev (chapter 1)",
            100,
            100,
            1024,
            768,
            0
    );


    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!mRenderer) {
        SDL_Log("Faild to create render node: %s", SDL_GetError());
        return false;
    }
    mPaddlerPos.x = 10.0f;
    mPaddlerPos.y = 768.0f/2.0f;
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;


    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
        mIsRunning = false;

    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W])
        mPaddleDir+=1;

    if (state[SDL_SCANCODE_S])
        mPaddleDir-=1;

}

void Game::UpdateGame() {

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount+16));


    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }


    mTicksCount = SDL_GetTicks();

    
    if (mPaddleDir != 0) {
        mPaddlerPos.y += mPaddleDir * 300.0f * deltaTime;

        if (mPaddlerPos.y < (paddleH / 2.0f + thickness))
            mPaddlerPos.y = paddleH / 2.0f + thickness;
        else if (mPaddlerPos.y > (768.0f - paddleH / 2.0f - thickness))
            mPaddlerPos.y = 768.0f - paddleH / 2.0f - thickness;
    }


}

void Game::GenerateOutput() {


    SDL_SetRenderDrawColor(mRenderer, 0, 0, 50, 255);

    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);


    SDL_Rect wall{
            0,
            0,
            1024,
            thickness
    };

    SDL_RenderFillRect(mRenderer, &wall);
    wall.y = 768 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;

    SDL_RenderFillRect(mRenderer, &wall);


    SDL_Rect ball{
            static_cast<int>(mBallPos.x - thickness / 2),
            static_cast<int>(mBallPos.y - thickness / 2),
            thickness,
            thickness
    };

    SDL_RenderFillRect(mRenderer, &ball);

    SDL_Rect paddle{
            static_cast<int>(mPaddlerPos.x),
            static_cast<int>(mPaddlerPos.y - paddleH/2),
            thickness,
            static_cast<int>(paddleH)
    };

    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_RenderPresent(mRenderer);

}






