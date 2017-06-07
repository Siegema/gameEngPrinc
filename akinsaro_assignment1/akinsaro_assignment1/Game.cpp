#include "Game.h"
#include "utils.h"

#include <iostream>
#include <vector> 

Game::Game()
	: mScreenWidth(800)
	, mScreenHeight(800)
	, mWindow(NULL)
	, mKeys(NULL)
	, mRenderer(NULL)
	, mShouldQuit(false)
	, LeftWall()
	, RightWall()
	, TopWall()
	, BottomWall()
	, mBall()
	, mBox()
	, mEntity()			// player can be fully configured later
	, mCenterSqr()
	, mEntities()
	, mIsDraggable(false)
{
}

bool Game::Run()
{
	// setup
	if (!Load()) {
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
		ProcessEvents();
		int updates = 0;
		while ((currentTime = SDL_GetTicks()) > gameTime && ++updates < FRAME_SKIP) {
			gameTime += DELTA_MS;
			Update(DELTA_F);
		}
		Draw();
	}

	// cleanup
	Shutdown();

	return true;
}

//Collision Check
string Game::Collided(Entity rect1, Entity rect2)
{
	if ((((rect1.Left() + rect1.Right())/2) >= rect2.Left() && 
		((rect1.Left() + rect1.Right())/2) <= ((rect2.Left() + rect2.Right())/2)) &&
	    rect1.Left() < rect2.Left() &&
		rect1.Bottom() > rect2.Top() &&
		rect1.Bottom() < rect2.Bottom()) {
		return "rTol";
	}//Right Colliding with Left
	if (((rect1.Top() + rect1.Bottom())/2) >= rect2.Top() &&
		rect1.Top() < rect2.Top() &&
		rect1.Right() >= rect2.Left() &&
		rect1.Left() <= rect2.Right()) {
		return "bTot";
	}//Bottom Colliding with Top
	if ((((rect1.Left() + rect1.Right())/2) < rect2.Right() && 
		((rect1.Left() + rect1.Right())/2) > ((rect2.Left() + rect2.Right())/2)) &&
	    rect1.Right() > rect2.Right() &&
		rect1.Bottom() > rect2.Top() &&
		rect1.Bottom() < rect2.Bottom()) {
		return "lTor";
	}//Left Colliding with Right
	if (((rect1.Top() + rect1.Bottom())/2) <= rect2.Bottom() &&
		rect1.Bottom() > rect2.Bottom() &&
		rect1.Right() >= rect2.Left() &&
		rect1.Left() <= rect2.Right()) {
		return "tTob";
	}//Top Colliding with Bottom
	return "noCol";
}

bool Game::Load()
{
	if (Game::msSeed != 0) {
		RandHelpers::randSeed(Game::msSeed);
	}
	else {
		RandHelpers::randSeed();
	}

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

	mCreatable = false;
	mRclicked = false;

	//
	// create a renderer that takes care of drawing stuff to the window
	//
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		std::cerr << "*** Failed to create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	// Making Layout
	LeftWall.SetWidth(30);
	LeftWall.SetHeight(mScreenHeight);
	LeftWall.SetLeft(0);
	LeftWall.SetColor(0, 0, 0, 255);

	RightWall.SetWidth(30);
	RightWall.SetHeight(mScreenHeight);
	RightWall.SetRight(mScreenWidth);
	RightWall.SetColor(0, 0, 0, 255);

	TopWall.SetHeight(30);
	TopWall.SetWidth(mScreenWidth);
	TopWall.SetTop(0);
	TopWall.SetColor(0, 0, 0, 255);

	BottomWall.SetHeight(30);
	BottomWall.SetWidth(mScreenWidth);
	BottomWall.SetBottom(mScreenHeight);
	BottomWall.SetColor(0, 0, 0, 255);

	mCenterSqr.SetWidth(200);
	mCenterSqr.SetHeight(200);
	mCenterSqr.SetCenter(mScreenWidth / 2, mScreenHeight / 2);
	mCenterSqr.SetColor(0, 0, 0, 255);

	mLayout.push_back(LeftWall);
	mLayout.push_back(TopWall);
	mLayout.push_back(RightWall);
	mLayout.push_back(BottomWall);
	mLayout.push_back(mCenterSqr);

	return true;
}

void Game::Shutdown()
{
	std::cout << "Shutting down game" << std::endl;

	// this closes the window and shuts down SDL
	SDL_Quit();
}


void Game::Update(float delta)
{
	if (!mBalls.empty()) {
		for (int i = 0; i < mBalls.size(); i++) {
			mBalls.at(i).Update(delta);

			//Function on line 58
			//Collision with Layout 
			for (int m = 0; m < mLayout.size(); m++) {
				if (Collided(mBalls.at(i), mLayout.at(m)).compare("rTol") == 0) {
					mBalls.at(i).SetVelocity(-1 * (mBalls.at(i).GetVelocityX()),
						(mBalls.at(i).GetVelocityY()));
				}
				if (Collided(mBalls.at(i), mLayout.at(m)).compare("bTot") == 0) {
					mBalls.at(i).SetVelocity((mBalls.at(i).GetVelocityX()),
						(-1 * (mBalls.at(i).GetVelocityY())));
				}
				if (Collided(mBalls.at(i), mLayout.at(m)).compare("lTor") == 0) {
					mBalls.at(i).SetVelocity(-1 * (mBalls.at(i).GetVelocityX()),
						((mBalls.at(i).GetVelocityY())));
				}
				if (Collided(mBalls.at(i), mLayout.at(m)).compare("tTob") == 0) {
					mBalls.at(i).SetVelocity((mBalls.at(i).GetVelocityX()),
						(-1 * (mBalls.at(i).GetVelocityY())));
				}
			}

			//Collision with temporary Boxes
			for (int m = 0; m < mEntities.size(); m++) {
				if (Collided(mBalls.at(i), mEntities.at(m)).compare("rTol") == 0) {
					mBalls.at(i).SetVelocity(-1 * (mBalls.at(i).GetVelocityX()),
						(mBalls.at(i).GetVelocityY()));
				}
				if (Collided(mBalls.at(i), mEntities.at(m)).compare("bTot") == 0) {
					mBalls.at(i).SetVelocity((mBalls.at(i).GetVelocityX()),
						(-1 * (mBalls.at(i).GetVelocityY())));
				}
				if (Collided(mBalls.at(i), mEntities.at(m)).compare("lTor") == 0) {
					mBalls.at(i).SetVelocity(-1 * (mBalls.at(i).GetVelocityX()),
						((mBalls.at(i).GetVelocityY())));
				}
				if (Collided(mBalls.at(i), mEntities.at(m)).compare("tTob") == 0) {
					mBalls.at(i).SetVelocity((mBalls.at(i).GetVelocityX()),
						(-1 * (mBalls.at(i).GetVelocityY())));
				}
			}
		}

		//meant To turn red when balls collide
		//for (int i = 0; i < mBalls.size(); i++) {
		//	if (Collided(mBalls.at(i), mBox).compare("rTol") == 0 ||
		//		Collided(mBalls.at(i), mBox).compare("lTor") == 0 ||
		//		Collided(mBalls.at(i), mBox).compare("tTob") == 0 ||
		//		Collided(mBalls.at(i), mBox).compare("bTot") == 0) {
		//		mBox.SetColor(255, 0, 0, 145);
		//	}
		//}
	}
}

void Game::Draw()
{
	// clear the screen
	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_RenderClear(mRenderer);

	//draw permanent boxes
	if (!mLayout.empty()) {
		for (int i = 0; i < mLayout.size(); i++) {
			mLayout.at(i).Draw(mRenderer);
		}
	}

	//Drawing the temporary Box
	mBox.Draw(mRenderer);


	if (!mEntities.empty()) {
		for (int i = 0; i < mEntities.size(); i++) {
			mEntities.at(i).Draw(mRenderer);
		}
	}

	//ball
	if (!mBalls.empty()) {
		for (int i = 0; i < mBalls.size(); i++) {
			mBalls.at(i).Draw(mRenderer);
		}
	}

	// tell the renderer to display everything we just drew
	SDL_RenderPresent(mRenderer);
}