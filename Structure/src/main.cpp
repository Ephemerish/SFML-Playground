#include "Game.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char** argv) {
	Game game;
	int count = 0;

	while (!game.GetWindow()->IsDone()) {
		std::cout << game.GetMushroomPosition().x << ", " << game.GetMushroomPosition().y << "\n";
		// game loop
		game.HandleInput();
		game.Update();
		game.Render();
		// restart clock
		game.RestartClock(); 
	}
}