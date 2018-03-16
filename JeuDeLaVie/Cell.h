#pragma once

#include <SFML/Graphics.hpp>

const sf::Color ALIVE = sf::Color::White;
const sf::Color DEAD = sf::Color::Black;


class Cell
{
public:
	Cell::Cell(bool isAlive = false,sf::Color color = ALIVE);
	~Cell();

	sf::Color getColor() const;
	bool isAlive() const;
	void setAlive(bool state);
	void setColor(sf::Color color);
	Cell& operator=(const Cell& other);

private:
	sf::Color m_color; // m_color[0] dead color m_color[1] alive color
	bool m_alive; // state of the cell
};

