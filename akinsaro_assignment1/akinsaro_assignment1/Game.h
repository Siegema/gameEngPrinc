#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "Entity.h"
#include <vector>

class Game
{
	int					mScreenWidth;
	int					mScreenHeight;

	SDL_Window*			mWindow;
	const Uint8*		mKeys;
	SDL_Renderer*		mRenderer;

	bool				mShouldQuit;

	Entity              mBox;
	Entity				mEntity;
	Entity              mBall;
	Entity              mCenterSqr;
	Entity				LeftWall;
	Entity				RightWall;
	Entity				TopWall;
	Entity				BottomWall;

	bool				mIsDraggable;
	bool                mCreatable;
	bool                mRclicked;//Right click

	float               mStartPointX;
	float               mStartPointY;
	float               endPointX;
	float               endPointY;

public:
	static int          msSeed;

						Game();

	bool				Run();

	static string		    Collided(Entity rect1, Entity rect2);

private:
	bool				Load();
	void				Shutdown();
	void                Clicked(Entity *selected, float x, float y);

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
	
	std::vector<Entity> mEntities;
	std::vector<Entity> mBalls;
	std::vector<Entity> mLayout;
};

#endif 