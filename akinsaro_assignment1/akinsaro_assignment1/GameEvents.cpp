#include "Game.h"
#include "utils.h"

#include <iostream>
#include <SDL.h>

void Game::ProcessEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			OnQuit();
			break;
		case SDL_KEYDOWN:
			OnKeyDown(&e.key);
			break;
		case SDL_KEYUP:
			OnKeyUp(&e.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(&e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseUp(&e.button);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMotion(&e.motion);
			break;
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				OnWindowResized(e.window.data1, e.window.data2);
			}
			break;
		default:
			break;
		}
	}
}

void Game::OnQuit()
{
	std::cout << "Application was told to quit" << std::endl;

	mShouldQuit = true;
}

void Game::OnWindowResized(int w, int h)
{
	std::cout << "Window resized to " << w << 'x' << h << std::endl;

	mScreenWidth = w;
	mScreenHeight = h;
}

void Game::OnKeyDown(const SDL_KeyboardEvent* kbe)
{
	switch (kbe->keysym.sym) {
	case SDLK_ESCAPE:
		std::cout << "User pressed Escape" << std::endl;
		mShouldQuit = true;  // set quit flag
		break;
	case SDLK_c:
		std::cout << "RESET" << std::endl;
		if (!mEntities.empty()) {
			mEntities.clear();
		}
		if (!mBalls.empty()) {
			mBalls.clear();
		}
		mBox.SetWidth(0);
		mBox.SetHeight(0);
		break;
	case SDLK_b:
		int static max = 30;
		int static count = 0;
		if (count < max) {
			//Creating Balls 
			mBall.SetLeft(70);
			mBall.SetTop(60);
			mBall.SetWidth(10);
			mBall.SetHeight(10);
			mBall.SetColor(255, 255, 255, 255);
			mBall.SetVelocity(RandHelpers::randInt(50, 100),
				RandHelpers::randInt(50, 100));
			mBalls.push_back(mBall);
			count++;
		}
		break;
	}
}

void Game::OnKeyUp(const SDL_KeyboardEvent* kbe)
{
}

void Game::OnMouseDown(const SDL_MouseButtonEvent* mbe)
{
	if (mbe->button == SDL_BUTTON_LEFT) {
		//drawing from these points
		mStartPointX = mbe->x;
		mStartPointY = mbe->y;
		mCreatable = true;
		mBox.SetColor(0, 0, 255, 145);
	}

	if (mbe->button == SDL_BUTTON_RIGHT) {
		if (!mEntities.empty()) {
			for (int i = 0; i < mEntities.size(); i++) {
				Clicked(&mEntities[i], mbe->x, mbe->y);
			}
		}
	}
}

void Game::Clicked(Entity * selected, float x, float y) {
	if (selected->Contains(x, y)) {
		selected->SetColor(255, 0, 0, 255);
		mRclicked = true;
	}
	else {
		selected->SetColor(0, 0, 255, 255);
		mRclicked = false;
	}
}

void Game::OnMouseUp(const SDL_MouseButtonEvent* mbe)
{
	static int limit = 20;
	static int boxNum = 0;
	if (mRclicked) {
		for (int i = 0; i < mEntities.size(); i++) {
			if (mEntities.at(i).Contains(mbe->x, mbe->y)) {
				mEntities.erase(mEntities.begin() + i);
			}
		}
	}
	else {
		mCreatable = false;
		mBox.SetColor(0, 0, 255, 255);
		if (boxNum < limit) {
			mEntities.push_back(mBox);
			mBox.SetWidth(0);
			mBox.SetHeight(0);
			boxNum++;
		}
	}
	mRclicked = false;
}

void Game::OnMouseMotion(const SDL_MouseMotionEvent* mme)
{
	float endPointX = mme->x;
	float endPointY = mme->y;

	if (mCreatable) {
		if (!mEntities.empty()) {
			for (int i = 0; i < mEntities.size(); i++) {
				if (!mEntities[i].Contains(mme->x, mme->y)) {
					mEntities[i].SetColor(0, 0, 255, 255);
					mRclicked = false;
				}
				if (((mEntities[i].Left() > mStartPointX && mEntities[i].Left() < endPointX)
					|| (mEntities[i].Right() < mStartPointX && mEntities[i].Right() > endPointX))
					&& ((mEntities[i].Top() > mStartPointY && mEntities[i].Top() < endPointY)
						|| (mEntities[i].Bottom() < mStartPointY && mEntities[i].Bottom() > endPointY))) {
					mBox.SetColor(255, 0, 0, 145);
				}
			}
		}
		mBox.SetLeft(mStartPointX);
		mBox.SetTop(mStartPointY);
		mBox.SetWidth(endPointX - mStartPointX);
		mBox.SetHeight(endPointY - mStartPointY);
	}

	for (int i = 0; i < mEntities.size(); i++) {
		if (mme->state == SDL_BUTTON_RMASK) {
			Clicked(&mEntities[i], mme->x, mme->y);
		}
	}
}