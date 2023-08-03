#include <SFML/Graphics.hpp>
#include <Windows.h>

int main(int argc, char** argv) {
	// Hide or Show Console
	ShowWindow(GetConsoleWindow(), SW_HIDE); // SW_SHOW to show

	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");

	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);		

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close Window
				window.close();
			}
		}
		window.clear(sf::Color::Cyan);
		// Draw here
		window.draw(rectangle);
		window.display();
	}
	
}