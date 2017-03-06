#include "Game.h"

//Namespace for textures ID values
namespace Textures
{
	enum class ID{Landscape, Airplane};
}

int main()
{
	Game game;
	game.run();
}