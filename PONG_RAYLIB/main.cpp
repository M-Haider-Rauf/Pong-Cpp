#include <iostream>
#include "Game.hpp"

int main()
{
	Game* game = Game::get_instance();
	game->main_loop();
}