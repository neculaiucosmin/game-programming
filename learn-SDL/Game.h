#pragma once
#include <SDL.h>

struct Vector2
{
	float x;
	float y;

};

class Game
{
public:
	Game();

	bool Initialize();
	//init game
	void RunLoop();
	//run game until is over
	void Shutdown();
	//shutdown game
private:
	//helpers for game loop


	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//Window created by SDL
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	Vector2 mBallPos;
    Vector2 mPaddlerPos;

    int mPaddleDir;


	//game should run
	bool mIsRunning;
    Uint32 mTicksCount;
};