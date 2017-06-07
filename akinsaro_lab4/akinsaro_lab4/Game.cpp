#include "Game.h"

#include <iostream>

Game::Game()
	: mScreenWidth(600)
	, mScreenHeight(600)
	, mWindow(NULL)
	, mKeys(NULL)
	, move(100.0)				//setting movement speed
	, mRenderer(NULL)
	, mShouldQuit(false)
	, mEntity(nullptr)			// Entity can be fully configured later
	, mGameState(0)
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


	//Mouse Location
	mousePos.x = 175.00;
	mousePos.y = 500.00;

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
	switch (mGameState) {
	case 0:
		mEntity = new Entity();
		mEntity->SetWidth(50);
		mEntity->SetHeight(60);
		mEntity->SetCenter(mScreenWidth, mScreenHeight);
		break;

	case 1:
		mEntity = new Entity();
		mEntity->SetWidth(50);
		mEntity->SetHeight(60);
		mEntity->SetLeft(rand() % (mScreenWidth - mEntity->Width()) + 0);
		mEntity->SetTop(rand() % (mScreenHeight - mEntity->Top()) + 0);
		break;

	case 2:
		mEntity = new Entity();
		mEntity->SetWidth(50);
		mEntity->SetHeight(60);
		mEntity->SetLeft(0);
		mEntity->SetTop(0);
		break;

	case 3:
		mEntity = new Entity();
		mEntity->SetWidth(50);
		mEntity->SetHeight(60);
		mEntity->SetLeft(rand() % (mScreenWidth - mEntity->Width()) + 0);
		mEntity->SetTop(rand() % (mScreenHeight - mEntity->Top()) + 0);
		break;

	case 4:
		mEntity = new Entity();
		mEntity->SetWidth(50);
		mEntity->SetHeight(60);
		mEntity->SetCenter(mScreenWidth, mScreenHeight);
		break;
	}
}


void Game::Shutdown()
{
	std::cout << "Shutting down game" << std::endl;

	// this closes the window and shuts down SDL
	SDL_Quit();
}

void Game::Movement() {
	if (mKeys[SDL_GetScancodeFromKey(SDLK_LSHIFT)]
		|| mKeys[SDL_GetScancodeFromKey(SDLK_RSHIFT)]) {
		move = 200;
		std::cout << "move is 200 " << std::endl;
	}
	else {
		move = 100;
	}

	if (mKeys[SDL_GetScancodeFromKey(SDLK_UP)]) {
		std::cout << "UP" << std::endl;
		mEntity->SetVelocity(0.0, -move);
	}
	if (mKeys[SDL_GetScancodeFromKey(SDLK_DOWN)]) {
		std::cout << "Down" << std::endl;
		mEntity->SetVelocity(0.0, move);
	}
	if (mKeys[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
		std::cout << "Left" << std::endl;
		mEntity->SetVelocity(-move, 0.0);
	}
	if (mKeys[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
		std::cout << "Right" << std::endl;
		mEntity->SetVelocity(move, 0.0);
	}

}

void Game::InScreen() {
	//Remain in the x bounds on the screen
	if (mEntity->Left() < 0) {
		mEntity->SetLeft(0);
	}
	if (mEntity->Right() > mScreenWidth) {
		mEntity->SetLeft(mScreenWidth - mEntity->Width());
	}

	//Remain in the y bounds on the screen
	if (mEntity->Top() < 0) {
		mEntity->SetTop(0);
	}
	if (mEntity->Bottom() > mScreenHeight) {
		mEntity->SetBottom(mScreenHeight);
	}
}

void Game::Update(float delta)
{
	//Make sure there is an entity to update
	if (mEntity != nullptr) {
		//Here you should check the keyboard state or the 
		// mouse position (depending on which game state
		// you are currently in) and set the entities
		// velocity accordingly

		switch (mGameState) {
		case 0:
			//Function Movement at line 161 
			//takes care of orthogonally movements
			Movement();
			break;

		case 1:
			Movement();
			//Function InScreen at line 190 
			//Keeps Entity in the game screen
			InScreen();
			break;

		case 2:
			Movement();

			//Diagonal Movement

			//UP&LEFT
			if (mKeys[SDL_GetScancodeFromKey(SDLK_UP)]
				&& mKeys[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
				mEntity->SetVelocity(-move, -move);
			}
			//UP&RIGHT
			if (mKeys[SDL_GetScancodeFromKey(SDLK_UP)]
				&& mKeys[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
				mEntity->SetVelocity(move, -move);
			}
			//DOWN&LEFT
			if (mKeys[SDL_GetScancodeFromKey(SDLK_DOWN)]
				&& mKeys[SDL_GetScancodeFromKey(SDLK_LEFT)]) {
				std::cout << "UP & Left" << std::endl;
				mEntity->SetVelocity(-move, move);
			}
			//DOWN&RIGHT
			if (mKeys[SDL_GetScancodeFromKey(SDLK_DOWN)]
				&& mKeys[SDL_GetScancodeFromKey(SDLK_RIGHT)]) {
				std::cout << "UP & Left" << std::endl;
				mEntity->SetVelocity(move, move);
			}

			InScreen();
			break;

		case 3:
			Movement();

			//Warp to other Side
			if ((mEntity->Left() + mEntity->Width() / 2) < 0) {
				mEntity->SetLeft(mScreenWidth);
			}
			if ((mEntity->Right() - mEntity->Width()) > mScreenWidth) {
				mEntity->SetRight(mEntity->Width() / 2);
			}

			if (mEntity->Top() + mEntity->Height() / 2 < 0) {
				mEntity->SetTop(mScreenHeight);
			}
			if ((mEntity->Bottom() - mEntity->Height()) > mScreenHeight) {
				mEntity->SetBottom(mEntity->Height() / 2);
			}
			break;

		case 4:
			//Movement();
			if (!(mEntity->Center().x == mousePos.x
				&& mEntity->Center().y == mousePos.y)) {

				//Ortho decisions
				if (mousePos.x < mEntity->Center().x) {
					mEntity->SetVelocity(-move, 0.0);
				}
				else if (mousePos.y < mEntity->Center().y) {
					mEntity->SetVelocity(0.0, -move);
				}
				if (mousePos.x > mEntity->Center().x) {
					mEntity->SetVelocity(move, 0.0);
				}
				else if (mousePos.y > mEntity->Center().y) {
					mEntity->SetVelocity(0.0, move);
				}


				//Diagonal decisions
				//Priority goes to diagonal by being called second

				//UP&LEFT
				if ((mousePos.x < mEntity->Center().x)
					&& (mousePos.y < mEntity->Center().y)) {
					mEntity->SetVelocity(-move, -move);
				}
				//DOWN&LEFT
				if ((mousePos.x < mEntity->Center().x)
					&& (mousePos.y > mEntity->Center().y)) {
					mEntity->SetVelocity(-move, move);
				}
				//DOWN&RIGHT
				if ((mousePos.x > mEntity->Center().x)
					&& (mousePos.y > mEntity->Center().y)) {
					mEntity->SetVelocity(move, move);
				}
				//UP&RIGHT
				if ((mousePos.x > mEntity->Center().x)
					&& (mousePos.y < mEntity->Center().y)) {
					mEntity->SetVelocity(move, -move);
				}
			}
			InScreen();
			break;
		}
	}


	//Now update the entity
	mEntity->Update(delta);

	//Reset afte update

	//This stops the Entity from continuous moving 
	if (mGameState != 3) {
		mEntity->SetVelocity(0.0, 0.0);
	}
}


void Game::Draw()
{
	// clear the screen
	SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, 255);
	SDL_RenderClear(mRenderer);

	//Make sure there is an entinty to draw
	if (mEntity != nullptr) {
		// draw Entity
		mEntity->Draw(mRenderer);
	}

	// tell the renderer to display everything we just drew
	SDL_RenderPresent(mRenderer);
}
