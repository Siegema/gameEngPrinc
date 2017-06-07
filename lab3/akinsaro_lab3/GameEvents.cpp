/*
*
*
*/
#include "Game.h"

#include <iostream>

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
	case SDLK_r:
		std::cout << "RESET" << std::endl;
		Game::Load();
    }
}

void Game::OnKeyUp(const SDL_KeyboardEvent* kbe)
{
}

void Game::OnMouseDown(const SDL_MouseButtonEvent* mbe)
{
	if (mbe->button == SDL_BUTTON_LEFT) {
		std::cout << "Left button pressed at (" << mbe->x << ", " << mbe->y << ")" << std::endl;

		// set player's top-left corner to mouse coordinates
		mEntity.SetLeft(mbe->x);
		mEntity.SetTop(mbe->y);

	} else if (mbe->button == SDL_BUTTON_RIGHT) {
		std::cout << "Right button pressed at (" << mbe->x << ", " << mbe->y << ")" << std::endl;

		// center player rect at the mouse coordinates
		mEntity.SetCenter(mbe->x, mbe->y);
	}
}

void Game::OnMouseUp(const SDL_MouseButtonEvent* mbe)
{
}

void Game::OnMouseMotion(const SDL_MouseMotionEvent* mme)
{
	// check if either the left or right buttons are pressed
	if (mme->state & (SDL_BUTTON_LMASK | SDL_BUTTON_RMASK)) {
		// move the player by the amount of cursor displacement
		mEntity.Move(mme->xrel, mme->yrel);
	}
}
