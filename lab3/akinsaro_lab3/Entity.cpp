#include "Entity.h"

const int Entity::msDefaultWidth = 64;
const int Entity::msDefaultHeight = 64;

const SDL_Color	Entity::msDefaultColor = { 255, 255, 255, 255 };		// white


Entity::Entity()
	: Entity(0, 0, msDefaultWidth, msDefaultHeight, msDefaultColor)		// C++11 delegating constructors ftw
{
}

Entity::Entity(int x, int y)
	: Entity(x, y, msDefaultWidth, msDefaultHeight, msDefaultColor)
{
}

Entity::Entity(int x, int y, int w, int h)
	: Entity(x, y, w, h, msDefaultColor)
{
}

Entity::Entity(int x, int y, int w, int h, SDL_Color color)
	: mRect()
	, mColor()
{
	mRect.x = x;
	mRect.y = y;
	mRect.w = w;
	mRect.h = h;
	mColor = color;		// struct bitwise copy
}

SDL_Point Entity::Center() const
{
	SDL_Point p;
	p.x = Left() + Width() / 2;
	p.y = Top() + Height() / 2;
	return p;
}

void Entity::SetCenter(int x, int y)
{
	SetLeft(x - Width() / 2);
	SetTop(y - Height() / 2);
}

void Entity::Move(int dx, int dy)
{
	mRect.x += dx;
	mRect.y += dy;
}

void Entity::Update(const Uint8* keys)
{
    //
    // update position based on current keyboard state
    //
    if (keys[SDL_SCANCODE_D]) {
        mRect.x += 2;
    }
    if (keys[SDL_SCANCODE_A]) {
        mRect.x -= 2;
    }
    if (keys[SDL_SCANCODE_W]) {
        mRect.y -= 2;
    }
    if (keys[SDL_SCANCODE_S]) {
        mRect.y += 2; 
    }
}

void Entity::Draw(SDL_Renderer* renderer) const
{
    // set new color for drawing
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    // draw the player sprite using the selected color
    SDL_RenderFillRect(renderer, &mRect);
}
