#include "Game.h"

////////// public //////////
Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),m_snake(m_world.GetBlockSize()), 
	m_world(sf::Vector2u(800, 600))
{
	m_textbox.Setup(5, 14, 190, sf::Vector2f(800 - 190, m_window.GetWindowSize().y - 84 - 20));
	m_textbox.Add("Seeded: " + std::to_string(time(NULL)));
}
Game:: ~Game() {}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& (m_snake.GetPhysicalDirection() != Direction::Down 
		|| m_snake.GetDirection() == Direction::None))
	{
		m_snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& (m_snake.GetPhysicalDirection() != Direction::Up
		|| m_snake.GetDirection() == Direction::None))
	{
		m_snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& (m_snake.GetPhysicalDirection() != Direction::Right
		|| m_snake.GetDirection() == Direction::None))
	{
		m_snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& (m_snake.GetPhysicalDirection() != Direction::Left
		|| m_snake.GetDirection() == Direction::None))
	{
		m_snake.SetDirection(Direction::Right);
	}
}
void Game::Update() {
	float timestep = 1.0f / m_snake.GetSpeed();
	if (m_elapsed >= sf::seconds(timestep)) {
		m_snake.Tick();
		m_world.Update(m_snake, m_textbox);
		m_elapsed -= sf::seconds(timestep);
		if (m_snake.HasLost()) {
			int maxX = (m_window.GetWindowSize().x / m_world.GetBlockSize()) - 2;
			int maxY = (m_window.GetWindowSize().y / m_world.GetBlockSize()) - 2;
			sf::Vector2i startPos(rand() % maxX + 1, rand() % maxY + 1);
			m_textbox.Add("You LOST! Score: " + std::to_string(m_snake.GetScore()));
			m_snake.Reset(startPos);
			m_world.RespawnApple();
		}
	}
}

void Game::Render() {
	// clear
	m_window.BeginDraw();
	// start drawing
	m_world.Render(m_window.GetRenderWindow());
	m_snake.Render(m_window.GetRenderWindow());
	m_textbox.Render(m_window.GetRenderWindow());
	// display
	m_window.EndDraw();
}
Window* Game::GetWindow() { return& m_window; }

sf::Time Game::GetElapsed() {
	return m_elapsed;
}
void Game::RestartClock() {
	m_elapsed += m_clock.restart();
	// std::cout << m_elapsed.asSeconds() << std::endl;
}

////////// private //////////
