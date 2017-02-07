/*
*Add a method prototype: done
*Add definition in game cpp: done
*/
#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>

#include "Entity.h"

class Game
{
	int					mScreenWidth;
	int					mScreenHeight;

	SDL_Window*			mWindow;
	const Uint8*		mKeys;
	SDL_Renderer*		mRenderer;

	bool				mShouldQuit;

	Entity				mEntity;

public:
						Game();

	bool				Run();

	//static int       	msSeed;

private:
	bool				Load();
	void				Shutdown();

	void				ProcessEvents();

	void				OnQuit();
	void				OnWindowResized(int w, int h);
	void				OnKeyDown(const SDL_KeyboardEvent* kbe);
	void				OnKeyUp(const SDL_KeyboardEvent* kbe);
	void				OnMouseDown(const SDL_MouseButtonEvent* mbe);
	void				OnMouseUp(const SDL_MouseButtonEvent* mbe);
	void				OnMouseMotion(const SDL_MouseMotionEvent* mme);

	void				Update();
	void				Draw();
};

#endif
