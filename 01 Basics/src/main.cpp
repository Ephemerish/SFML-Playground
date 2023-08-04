#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>

int main(int argc, char** argv) {
	// Hide or Show Console
	ShowWindow(GetConsoleWindow(), SW_SHOW); // SW_SHOW to show

	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");

	// Rectagle
	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

	// Mushroom
	sf::Texture mushroomTexture;
	mushroomTexture.loadFromFile("Mushroom.png");
	sf::Sprite mushroom(mushroomTexture);
	sf::Vector2u size = mushroomTexture.getSize();
	mushroom.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.2f, 0.2f);

	while(window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close Window
				window.close();
			}
		}

		// game logic

		if ((mushroom.getPosition().x + (size.x / 2) >
			window.getSize().x && increment.x > 0) ||
			(mushroom.getPosition().x - (size.x / 2) < 0 &&
				increment.x < 0))
		{
			// Reverse the direction on X axis
			increment.x = -increment.x;
		}
		if ((mushroom.getPosition().y + (size.y / 2) >
			window.getSize().y && increment.y > 0) ||
			(mushroom.getPosition().y - (size.y / 2) < 0 &&
				increment.y < 0))
		{// Reverse the direction on Y axis
			increment.y = -increment.y;
		}
		mushroom.setPosition(mushroom.getPosition() + increment);
		std::cout << mushroom.getPosition().x << ", " << mushroom.getPosition().y;
		std::cout << " || " << increment.x << ", " << increment.y << "\n";

		// clear screen
		window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.

		window.draw(mushroom); // Drawing our sprite
		window.draw(rectangle); // Drawing our rectagle above  the sprite
		window.display();
	}
	
}