#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <cstdlib>     // srand
#include <ctime>

namespace RandHelpers {
	void inline  randSeed() { srand(time(NULL)); }

	void inline randSeed(int seed) { srand(seed); }
 
	int randInt(int lower, int upper);
	
	SDL_Point randPoint(int x, int y, int w, int h);

	SDL_Point randPoint(SDL_Rect rect);

	SDL_Color randColor();

	SDL_Color brighColor();
}
#endif // !UTILS_H
