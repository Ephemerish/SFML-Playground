#pragma once
#include "SFML/Graphics.hpp"

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position(x, y) {};
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {	None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(int l_blockSize);
	~Snake();

	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	int GetLives();
	int GetScore();
	sf::Vector2i GetPosition();
	Direction GetPhysicalDirection();

	void IncreaseScore();
	bool HasLost();

	void Tick();
	void Extend();
	void Reset(sf::Vector2i l_startPos);

	void Cut(int l_segments); // Method for cutting snake.
	void Render(sf::RenderWindow& l_window);

	void ToggleLost();
	void Lose();

private:
	void Move();
	void CheckCollision();

	SnakeContainer m_snakeBody; // Snake Segment Vector
	sf::Vector2u m_windowSize;
	int m_size;
	int m_speed;
	Direction m_dir;
	int m_lives;
	int m_score;
	bool m_lost;

	sf::RectangleShape m_bodyRect; // Snake Segment Shape
};

