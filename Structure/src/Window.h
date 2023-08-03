#pragma once

#include <String>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();

	sf::Vector2u GetWindowSize();

	void ToggleFullscreeen();

	void Draw(sf::Drawable& l_drawable);

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};

