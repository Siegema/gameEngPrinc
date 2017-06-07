#include <iostream>
#include <SDL.h>

#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	/*
	game.msSeed = 0;
	if (argc > 0) {
		if (isdigit(*argv[0])) {
			game.msSeed = *argv[0];
		}
	}*/

	std::cout << "Hello" << std::endl;

	if (!game.Run()) {
		std::cerr << "*** Something horrible has happened" << std::endl;
		return 1;
	}

    std::cout << "Goodbye" << std::endl;

	return 0;
}
