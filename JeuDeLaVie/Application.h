#pragma once

#include "Grid.h"
#include "Cell.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>


#ifdef DEBUG
#include <iostream>
#endif // DEBUG


typedef struct
{
	sf::Color color;
	int count;
}COLOR;


class Application
{
public:
	Application(sf::RenderTarget *target,sf::Vector2u size);
	Application(sf::RenderTarget *target,sf::Vector2u size, double proba);
	Application(sf::RenderTarget *target, const Grid& grid);
	~Application();

	std::vector<Grid> trajectory(size_t n);
	Grid& getCurrentGrid();
	sf::Vector2u getSize() const;
	size_t getEtape() const;
	void nextGrid();
	void setGrid(Grid& other);
	void resetGrid();
	void fillGrid(double proba);
	void display() const;
	void countAlive();
	void eraseCell(sf::Vector2i mouse);
	void createCell(sf::Vector2i mouse, sf::Color color);
	unsigned int getAlive() const;
	sf::Color randomColor() const;
private:

	Cell checkCell(sf::Vector2u index, const Grid & grid) const;
	void createGrid(double proba);
	size_t m_alive_count;

	Grid m_grid;
	sf::Vector2u m_size;
	size_t m_etape;
	sf::RenderTarget *m_target;

};

