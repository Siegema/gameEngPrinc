#include "Entity.h"
#include <iostream>

const int Entity::msDefaultWidth = 64;
const int Entity::msDefaultHeight = 64;

const SDL_Color	Entity::msDefaultColor = { 255, 255, 255, 255 };		


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

float Entity::GetVelocityX() {
	return mVelocityX;
}

float Entity::GetVelocityY() {
	return mVelocityY;
}

void Entity::SetVelocity(float vx, float vy) {
	mVelocityX = vx;
	mVelocityY = vy;
}

void Entity::Update(float delta) {
	float dx = GetVelocityX() * delta;
	float dy = GetVelocityY() * delta;
	Move(dx, dy);
}

void Entity::Draw(SDL_Renderer* renderer) const
{
    // set new color for drawing
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);

    // draw the player sprite using the selected color
    SDL_RenderFillRect(renderer, &mRect);
}


bool Entity::Contains(float x, float y) const {
    if(Left() < x && Right() > x
		&& (Top() < y && Bottom() > y)) {
		std::cout << "true" << std::endl;
		return true;
	}
	else 
		return false;
} 