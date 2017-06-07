#include "utils.h"
#include <iostream>

namespace RandHelpers {

	int randInt(int lower, int upper) {
		int results = rand() % upper + lower;
		return results;
	}

	SDL_Point randPoint(int x, int y, int w, int h) {
		SDL_Point p;
		p.x = rand() % w + x;
		p.y = rand() % h + y;
		return p;
	}

	SDL_Point randPoint(SDL_Rect rect) {
		SDL_Point p;
		p.x = rand() % rect.w + rect.x;
		p.x = rand() % rect.h + rect.y;
		return p;
	}

	SDL_Color randColor() {
		SDL_Color c;
		c.r = rand() % 255;
		c.g = rand() % 255;
		c.b = rand() % 255;
		c.a = 255;
		return c;
	}

	SDL_Color brighColor() {
		SDL_Color c;
		c.r = 0.2126 * (rand() % 0, 255);
		c.g = 0.7152 * (rand() % 0, 255);
		c.b = 0.0722 * (rand() % 0, 255);
		c.a = 255;
		return c;
	}
}
