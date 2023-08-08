#include "Game.h"

int main(int argc, char** argv) {
	Game game;

	// game loop
	while (!game.GetWindow()->IsDone()) {

		std::cout << game.GetMushroomPosition().x << ", " << game.GetMushroomPosition().y;
		std::cout << " || " << game.GetMushroomSpeed().x << ", " << game.GetMushroomSpeed().y << "\n";

		game.HandleInput();
		game.Update();
		game.Render();

		// restart clock
		game.RestartClock(); 
	}
}