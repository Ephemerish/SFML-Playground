#include "Game.h"

////////// public //////////
Game::Game() : m_window("Ravioli", sf::Vector2u(800, 600)) {
	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_increment = sf::Vector2i(400, 400); // 400px per second
	}
Game:: ~Game() {}

void Game::HandleInput() {}
void Game::Update() {
	m_window.Update();
	MoveMushroom();
}

void Game::Render() {
	// clear
	m_window.BeginDraw();
	// start drawing
	m_window.Draw(m_mushroom);
	// display
	m_window.EndDraw();
}
Window* Game::GetWindow() { return& m_window; }

sf::Time Game::GetElapsed() {
	return m_elapsed;
}
void Game::RestartClock() {
	m_elapsed = m_clock.restart();
}

sf::Vector2f Game::GetMushroomPosition() {
	return m_mushroom.getPosition();
}

////////// private //////////
void Game::MoveMushroom() {
	float fElapased = m_elapsed.asSeconds();

	sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_mushroomTexture.getSize();
	if ((m_mushroom.getPosition().x >
		l_windSize.x - l_textSize.x && m_increment.x > 0) ||
		(m_mushroom.getPosition().x < 0 && m_increment.x < 0)) {
		m_increment.x = -m_increment.x;
	}
	if ((m_mushroom.getPosition().y >
		l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_mushroom.getPosition().y < 0 && m_increment.y < 0)) {
		m_increment.y = -m_increment.y;
	}
	m_mushroom.setPosition(
		m_mushroom.getPosition().x + m_increment.x * fElapased,
		m_mushroom.getPosition().y + m_increment.y * fElapased);
}