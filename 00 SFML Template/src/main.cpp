#include <SFML/Graphics.hpp>
#include <Windows.h>

int main(int argc, char** argv) {
	// Hide or Show Console
	ShowWindow(GetConsoleWindow(), SW_HIDE); // SW_SHOW to show

	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close Window
				window.close();
			}
		}
		window.clear(sf::Color::Cyan);
		// Draw here
		window.display();
	}

}