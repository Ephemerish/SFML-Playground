#pragma once
#include "Window.h"
#include "World.h"
#include "Textbox.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();
private:
	World m_world;
	Snake m_snake;
	Textbox m_textbox;

	Window m_window;

	sf::Vector2i m_speed;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};

