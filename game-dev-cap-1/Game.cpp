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
        SDL_Log("Failed to create render node: %s", SDL_GetError());
        return false;
    }
    //setup left paddler position
    mPaddlerPos.x = 10.0f;
    mPaddlerPos.y = 768.0f / 2.0f;
    //setup right paddler position
    mSecondPaddlerPos.x = 1000.0f;
    mSecondPaddlerPos.y = 768.0f/2.0f;
    //ball setup
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;
    mBallVel.x = -200.0f;
    mBallVel.y = 235.0f;


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


    //allow paddlers to move on keyboard events
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_S])
        mPaddleDir++;
    if (state[SDL_SCANCODE_W])
        mPaddleDir--;

    mSecondPaddlerDir = 0;
    if (state[SDL_SCANCODE_I])
        mSecondPaddlerDir--;
    if (state[SDL_SCANCODE_K])
        mSecondPaddlerDir++;
}

void Game::UpdateGame() {

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();


    //left paddler
    if (mPaddleDir != 0) {
        mPaddlerPos.y += mPaddleDir * 300.0f * deltaTime;

        if (mPaddlerPos.y < (paddleH / 2.0f + thickness))
            mPaddlerPos.y = paddleH / 2.0f + thickness;
        else if (mPaddlerPos.y > (768.0f - paddleH / 2.0f - thickness))
            mPaddlerPos.y = 768.0f - paddleH / 2.0f - thickness;
    }

    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
        mBallVel.y *= -1;

    float diff = mBallPos.y - mPaddlerPos.y;
    diff <= (diff > 0.0f) ? diff : -diff;
    SDL_Log("Diff: %d", diff);

    if (
            diff <= paddleH / 2.0f &&
            mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
            mBallVel.x < 0.0f
            ) {
        mBallVel.x *= -1.0f;
    } else if (mBallPos.x <= 0.0f) {
      mIsRunning = false;
    }
//    else if(mBallPos.x >= (1000.0f) && mBallVel.x > 0.0f){
//        mBallVel.x *= -1.0f;
//    }

    if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
        mBallVel.y *= -1;
    else if (mBallPos.y >= (768 - thickness) && mBallPos.y > 0.0f )
        mBallVel.y *= -1;

    //right paddler

    if (mSecondPaddlerDir != 0){
        mSecondPaddlerPos.y += mSecondPaddlerDir * 300.f * deltaTime;

        if(mSecondPaddlerPos.y < (paddleH / 2.0f + thickness))
            mSecondPaddlerPos.y = paddleH / 2.0f + thickness;
        else if ( mSecondPaddlerPos.y > (768.0f - paddleH / 2.0f -thickness))
            mSecondPaddlerPos.x = 786.0f - paddleH / 2.0 - thickness;
    }


    float diff2 = mBallPos.y - mSecondPaddlerPos.y ;
    //SDL_Log("poz ball: %f            poz paddler: %f      diff: %f", mBallPos.y, mSecondPaddlerPos.y, diff2);
    diff2 = (diff2 > 0.0f) ? diff2 : -diff2;
    if (
            diff2<=paddleH/2.0f &&
            mBallPos.x <= 1010.f && mBallPos.x > 1000.0f &&
            mBallVel.x >0.0f

            ){
        SDL_Log("Merge, din pacate");
        mBallVel.x *= -1.0f;
    } else if(mBallPos.x >= 1024.0f){
        mIsRunning = false;
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
    //wall.h = 1024;

    SDL_RenderFillRect(mRenderer, &wall);


    SDL_Rect ball{
            static_cast<int>(mBallPos.x - thickness / 2),
            static_cast<int>(mBallPos.y - thickness / 2),
            thickness,
            thickness
    };

    SDL_RenderFillRect(mRenderer, &ball);
    //paddler render done
    SDL_Rect paddle{
            static_cast<int>(mPaddlerPos.x),
            static_cast<int>(mPaddlerPos.y - paddleH / 2),
            thickness,
            static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_Rect secondPaddler{
        static_cast<int>(mSecondPaddlerPos.x),
        static_cast<int>(mSecondPaddlerPos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &secondPaddler);

    SDL_RenderPresent(mRenderer);
}
