#include <stdexcept>

#include "Game.h"


int main()
{
	try {
		Game game;
		game.run();
	}
	catch (std::runtime_error& e) {
		printf("EXCEPTION: %s\n", e.what());
	}

	return 0;
}