#include "Game.h"
#include "Textures.h"



int main()
{
	Textures textures;

	Game game(&textures);

	game.play();
	
	return 0;	
}