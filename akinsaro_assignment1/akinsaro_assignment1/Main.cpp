#include <iostream>
#include <SDL.h>

#include "Game.h"

int Game::msSeed = 0;

int main(int argc, char** argv)
{
	Game game;
 
	std::cout << argc << std::endl;

	if (argc > 1) {
		if (isdigit(*argv[1])) {
			game.msSeed = *argv[1];
			std::cout << game.msSeed << std::endl;
			std::cout << "is a number" << std::endl;
		}
		else {
			game.msSeed = 0;
			std::cout << "Argument ignored should a put int a number" << std::endl;
		}
	}

	std::cout << "Hello" << std::endl;

	if (!game.Run()) {
		std::cerr << "*** Something horrible has happened" << std::endl;
		return 1;
	}

	std::cout << "Goodbye" << std::endl;

	return 0;
}
