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

	Entity *			mEntity;
	int					mGameState;

public:
						Game();

	bool				Run();

private:
	bool				Initialize();
	void				Load();
	void				Shutdown();

	void				ProcessEvents();

	void				OnQuit();
	void				OnWindowResized(int w, int h);
	void				OnKeyDown(const SDL_KeyboardEvent* kbe);
	void				OnKeyUp(const SDL_KeyboardEvent* kbe);
	void				OnMouseDown(const SDL_MouseButtonEvent* mbe);
	void				OnMouseUp(const SDL_MouseButtonEvent* mbe);
	void				OnMouseMotion(const SDL_MouseMotionEvent* mme);

	void				Update(float delta);
	void				Draw();

	//I added
    SDL_Point 			mousePos;//Mouse Position
	float               move; //Movement speed
	void				Movement(); //holding ortho movements
	void				InScreen(); //Make sure it's in the screen
};

#endif 