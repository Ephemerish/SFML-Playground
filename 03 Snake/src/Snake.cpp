#include "Snake.h"

////////// public //////////
Snake::Snake(int l_blockSize) {
	m_size = l_blockSize;
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	Reset(sf::Vector2i(10, 10));
}
Snake::~Snake() {}

void Snake::SetDirection(Direction l_dir) { m_dir = l_dir; }
Direction Snake::GetDirection() { return m_dir; }
int Snake::GetSpeed() { return m_speed; }
int Snake::GetLives() { return m_lives; }
int Snake::GetScore() { return m_score; }
sf::Vector2i Snake::GetPosition(){
	return !m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1);
}
Direction Snake::GetPhysicalDirection() {
	if (m_snakeBody.size() <= 1) {
		return Direction::None;
	}

	SnakeSegment& head = m_snakeBody[0];
	SnakeSegment& neck = m_snakeBody[1];

	if (head.position.x == neck.position.x) {
		return (head.position.y > neck.position.y) ? Direction::Down : Direction::Up;
	} else if (head.position.y == neck.position.y) {
		return (head.position.x > neck.position.x) ? Direction::Right : Direction::Left;
	}

	return Direction::None;;
}

void Snake::IncreaseScore() { m_score += 100; }
bool Snake::HasLost() { return m_lost; }

void Snake::Tick() {
	if (m_snakeBody.empty()) { return; }
	if (m_dir == Direction::None) { return; }
	Move();
	CheckCollision();
}
void Snake::Extend() {
	if (m_snakeBody.empty()) { return; }
	
	SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];

	if (m_snakeBody.size() > 1) {
		SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			} else {
				m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		} else if(tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			else {
				m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	} else {
		if (m_dir == Direction::Up) {
			m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		} else if (m_dir == Direction::Down) {
			m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		} else if (m_dir == Direction::Left) {
			m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		} else if (m_dir == Direction::Right) {
			m_snakeBody.emplace_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}
//Move Snake to Starting Position
void Snake::Reset(sf::Vector2i l_startPos) {
	m_snakeBody.clear();
	int startingSize = 3;

	for (int i = 0; i < startingSize; i++) {
		m_snakeBody.push_back(SnakeSegment(l_startPos.x, l_startPos.y));
	}

	SetDirection(Direction::None);
	m_speed = 10;
	m_lives = 1;
	m_score = 0;
	m_lost = false;
}

// Method for cutting snake.
void Snake::Cut(int l_segments) {
	for (int i = 0; i < l_segments; ++i) {
		m_snakeBody.pop_back();
	}
	m_lives--;
	if (!m_lives) {
		Lose();
		return;
	}
}
void Snake::Render(sf::RenderWindow& l_window) {
	if (m_snakeBody.empty()) { return; }

	SnakeContainer::iterator head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	l_window.draw(m_bodyRect);

	m_bodyRect.setFillColor(sf::Color::Green);
	for (SnakeContainer::iterator itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); itr++) {
		m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
		l_window.draw(m_bodyRect);
	}
}

void Snake::ToggleLost() { m_lost = !m_lost; }
void Snake::Lose() { m_lost = true; }

////////// private //////////
void Snake::Move() {
	for (int i = m_snakeBody.size() - 1; i > 0; --i) {
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}
	if (m_dir == Direction::Up) {
		m_snakeBody[0].position.y--;
	} else if (m_dir == Direction::Down) {
		m_snakeBody[0].position.y++;
	} else if (m_dir == Direction::Left) {
		m_snakeBody[0].position.x--;
	} else if (m_dir == Direction::Right) {
		m_snakeBody[0].position.x++;
	} 
}
void Snake::CheckCollision() {
	if (m_snakeBody.size() < 5) { return; }
	SnakeSegment& head = m_snakeBody.front();
	for (SnakeContainer::iterator itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); itr++) {
		if (itr->position == head.position) {
			int segmentsToCut = m_snakeBody.end() - itr;
			Cut(segmentsToCut);
			break;
		} 
	}
}