/*
*Change Game::Initialize to Game::Load: 3/4
**Updated References: Done
*Added reset on R button: Maybe
*/
#include "Game.h"

#include <iostream>

Game::Game()
	: mScreenWidth(400)
	, mScreenHeight(600)
	, mWindow(NULL)
	, mKeys(NULL)
	, mRenderer(NULL)
	, mShouldQuit(false)
	, mEntity()			// player can be fully configured later
{
}

bool Game::Run()
{
	// setup
	if (!Load()) {
		std::cerr << "*** Game initialization failed" << std::endl;
		return false;
	}

	// game loop
	while (!mShouldQuit) {
		ProcessEvents();
		Update();
		Draw();
	}

	// cleanup
	Shutdown();

	return true;
}

bool Game::Load()
{
    std::cout << "Initializing game" << std::endl;

	//
	// initialize SDL
	//
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "*** Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	//
	// create a window
	//
	mWindow = SDL_CreateWindow("Hello, SDL2!",
								SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								mScreenWidth, mScreenHeight,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!mWindow) {
		std::cerr << "*** Failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//
	// get a pointer to keyboard state managed by SDL
	//
	mKeys = SDL_GetKeyboardState(NULL);

	//
	// create a renderer that takes care of drawing stuff to the window
	//
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		std::cerr << "*** Failed to create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	//
	// initialize the player
	//
	mEntity.SetWidth(64);
	mEntity.SetHeight(80);
	mEntity.SetCenter(mScreenWidth / 2, mScreenHeight / 2);
	mEntity.SetColor(192, 0, 164, 255);

	return true;
}

void Game::Shutdown()
{
    std::cout << "Shutting down game" << std::endl;

	// this closes the window and shuts down SDL
    SDL_Quit();
}

void Game::Update()
{
	mEntity.Update(mKeys);
}

void Game::Draw()
{
    // clear the screen
    SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, 255);
    SDL_RenderClear(mRenderer);

	// draw player
	mEntity.Draw(mRenderer);

    // tell the renderer to display everything we just drew
    SDL_RenderPresent(mRenderer);
}
