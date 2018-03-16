#pragma once

#include "Cell.h"
#include <SFML\Graphics.hpp>

class Grid
{
public:
	Grid(sf::Vector2u size);
	Grid(const Grid& other);
	~Grid();

	sf::Vector2u getSize() const;
	Cell getCell(sf::Vector2u index) const;
	void setCell(const Cell& value, sf::Vector2u index);
	
	Grid& operator=(const Grid& other);
	Cell& getCell(sf::Vector2u index);
	bool isInRange(sf::Vector2i index) const;
	bool isInRange(sf::Vector2u index) const;

private:
	Cell** m_grid;
	sf::Vector2u m_size;

};

