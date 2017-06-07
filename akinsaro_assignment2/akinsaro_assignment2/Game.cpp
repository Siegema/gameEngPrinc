#include "Game.h"

#include <iostream>

Game::Game()
	: mScreenWidth(800)
	, mScreenHeight(350)
	, mWindow(NULL)
	, mKeys(NULL)
	, move(100.0)				//setting movement speed
	, mRenderer(NULL)
	, mShouldQuit(false)
	, mEntity()	
	, mEntity2()	
	, ball()			
	, mGameState(0)
	, score{0,0}
{
}

bool Game::Run()
{
	// setup
	if (!Initialize()) {
		std::cerr << "*** Game initialization failed" << std::endl;
		return false;
	}
	float const FPS = 30.0f;
	float const DELTA_F = 1.0f / FPS;
	unsigned int const DELTA_MS = (int)(DELTA_F * 1000.0f);
	unsigned int currentTime = SDL_GetTicks();
	unsigned int gameTime = currentTime;
	int const FRAME_SKIP = 6;

	// game loop
	while (!mShouldQuit) {
		//Handle events
		ProcessEvents();
		//Update game entities
		int updates = 0;
		while ((currentTime = SDL_GetTicks()) > gameTime && ++updates < FRAME_SKIP) {
			gameTime += DELTA_MS;
			Update(DELTA_F);
		}
		//Render
		Draw();
	}

	// cleanup
	Shutdown();

	return true;
}

bool Game::Initialize()
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

	Load();

	return true;
}

void Game::Load()
{
	//Clean up any existing entities (if necessary)
	// Since we never leave dangling pointers this should be easy to check.

//	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		std::cerr << "*** Failed to create renderer: " << SDL_GetError() << std::endl;
	}

	//Now load the new game state according to the instructions
	mEntity.SetWidth(10);
	mEntity.SetHeight(50);
	mEntity.SetRight(mScreenWidth - 50);
	mEntities.push_back(&mEntity);

	mEntity2.SetWidth(10);
	mEntity2.SetHeight(50);
	mEntity2.SetLeft(50);
	mEntities.push_back(&mEntity2);

	ball.SetWidth(10);
	ball.SetHeight(10);
	ball.SetCenter(mScreenWidth, mScreenHeight);
	ball.SetColor(0, 255, 255, 255);
	ball.SetVelocity(80, 0);
}


void Game::Shutdown()
{
	std::cout << "Shutting down game" << std::endl;

	// this closes the window and shuts down SDL
	SDL_Quit();
}

void Game::Movement() {
	move = 100;

	if (mKeys[SDL_GetScancodeFromKey(SDLK_UP)]) {
		std::cout << "UP" << std::endl;
		mEntity.SetVelocity(0.0, -move);
	}
	if (mKeys[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
		std::cout << "Down" << std::endl;
		mEntity.SetVelocity(0.0, move);
	}

	if (mKeys[SDL_GetScancodeFromKey(SDLK_w)]) {
		std::cout << "UP" << std::endl;
		mEntity2.SetVelocity(0.0, -move);
	}
	if (mKeys[SDL_GetScancodeFromKey(SDLK_s)]) {
		std::cout << "Down" << std::endl;
		mEntity2.SetVelocity(0.0, move);
	}
}

void Game::InScreen() {
	//Remain in the y bounds on the screen
	if (mEntity.Top() < 0) {
		mEntity.SetTop(0);
	}
	if (mEntity.Bottom() > mScreenHeight) {
		mEntity.SetBottom(mScreenHeight);
	}

	if (mEntity2.Top() < 0) {
		mEntity2.SetTop(0);
	}
	if (mEntity2.Bottom() > mScreenHeight) {
		mEntity2.SetBottom(mScreenHeight);
	}
 
	if (ball.Top() < 0) {
		ball.SetVelocity(ball.GetVelocityX(), -1 * (ball.GetVelocityY()));
	}
	if (ball.Bottom() > mScreenHeight) {
		ball.SetVelocity(ball.GetVelocityX(), -1 * (ball.GetVelocityY()));
	}
}

void Game::Update(float delta)
{
	//Make sure there is an entity to update
	if (&mEntity != nullptr) {
		Movement();
	}

	ball.Update(delta);

	if ((ball.Left() + ball.Width() / 2) < 0) {
		ball.SetCenter(mScreenWidth, mScreenHeight);
		score[1]++;
		std::cout << score[0] << "    " << score[1] << std::endl;
	}
	if ((ball.Right() - ball.Width()) > mScreenWidth) {
		ball.SetCenter(mScreenWidth, mScreenHeight);
		score[0]++;
		std::cout << score[0] << "    " << score[1] << std::endl;
	}
	if (ball.Intersect(&mEntity) || ball.Intersect(&mEntity2)) {
		for (std::vector<Entity*>::const_iterator it = mEntities.begin();
			it < mEntities.end(); it++) {

			//need to be reinitialized
			float sectionSize = (*it)->Height() / 5;
			float sec1 = (*it)->Top() + sectionSize;
			float sec2 = sec1 + sectionSize;
			float sec3 = sec2 + sectionSize;
			float sec4 = sec3 + sectionSize;
			float sec5 = sec4 + sectionSize;

			if (ball.Top() < sec1) {
				ball.SetVelocity((-1 * (ball.GetVelocityX())), (-100));
			}
			else if (ball.Top() < sec2) {
				ball.SetVelocity((-1 * (ball.GetVelocityX())), (-75));
			}
			else if (ball.Top() < sec3) {
				ball.SetVelocity((-1 * (ball.GetVelocityX())), (0));
			}
			else if (ball.Top() < sec4) {
				ball.SetVelocity((-1 * (ball.GetVelocityX())), (75));
			}
			else if (ball.Top() < sec5) {
				ball.SetVelocity((-1 * (ball.GetVelocityX())), (100));
			}
		}
	}

	//Now update the entity
	mEntity.Update(delta);

	mEntity2.Update(delta);

	//Reset after update

	//This stops the Entity from continuous moving 
	mEntity.SetVelocity(0.0, 0.0);
	mEntity2.SetVelocity(0.0, 0.0);
	InScreen();
}


void Game::Draw()
{
	// clear the screen
	SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, 255);
	SDL_RenderClear(mRenderer);

	//Make sure there is an entinty to draw
	if (&mEntity != nullptr) {
		// draw Entity
		mEntity.Draw(mRenderer);
	}

	if (&mEntity2 != nullptr) {
		// draw Entity
		mEntity2.Draw(mRenderer);

	}

	if (&ball != nullptr) {
		ball.Draw(mRenderer);
	}

	// tell the renderer to display everything we just drew
	SDL_RenderPresent(mRenderer);
}