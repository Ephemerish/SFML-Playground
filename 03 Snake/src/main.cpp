#include "Game.h"

int main(int argc, char** argv) {
	Game game;

	// game loop
	while (!game.GetWindow()->IsDone()) {

		game.HandleInput();
		game.Update();
		game.Render();

		// restart clock
		game.RestartClock(); 
	}
}