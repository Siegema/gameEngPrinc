#ifndef Entity_H_
#define Entity_H_

#include <SDL.h>

class Entity
{
	SDL_Rect				mRect;
	SDL_Color				mColor;
	float					mVelocityX;
	float					mVelocityY;

public:
							Entity();
							Entity(int x, int y);
							Entity(int x, int y, int w, int h);
							Entity(int x, int y, int w, int h, SDL_Color color);


	int						Width() const		{ return mRect.w; }
	int						Height() const		{ return mRect.h; }

	int						Left() const		{ return mRect.x; }
	int						Top() const			{ return mRect.y; }
	int						Right() const		{ return mRect.x + mRect.w; }
	int						Bottom() const		{ return mRect.y + mRect.h; }

	SDL_Point				Center() const;
	SDL_Rect				BoundingBox() const;

	void					SetLeft(int x)		{ mRect.x = x; }
	void					SetRight(int x)		{ mRect.x = x - mRect.w; }
	void					SetTop(int y)		{ mRect.y = y; }
	void					SetBottom(int y)	{ mRect.y = y - mRect.h; }

	void					SetWidth(int w)		{ mRect.w = w; }
	void					SetHeight(int h)	{ mRect.h = h; }

	void					SetCenter(int x, int y);

	void					Move(int dx, int dy);
	float					GetVelocityX();
	float					GetVelocityY();
	void					SetVelocity(float vx, float vy);

	void					SetColor(SDL_Color color)						{ mColor = color; }
	void					SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)	{ mColor.r = r; mColor.g = g; mColor.b = b; mColor.a = a; }

	void					Update(float delta);
	void					Draw(SDL_Renderer* renderer) const;
	bool					Intersect(const Entity *ent2);

private:
	static const int		msDefaultWidth;
	static const int		msDefaultHeight;

	static const SDL_Color	msDefaultColor;
};

#endif
