#include "Grid.h"


Grid::Grid(sf::Vector2u size)
{
	this->m_size = size;
	this->m_grid = new Cell*[size.x];
	for (size_t i = 0; i < size.x; i++)
	{
		this->m_grid[i] = new Cell[size.y];
	}
}

Grid::Grid(const Grid& other)
{
	this->m_size = other.getSize();
	this->m_grid = new Cell*[this->m_size.x];
	for (unsigned int i = 0; i < this->m_size.x; i++)
	{
		this->m_grid[i] = new Cell[this->m_size.y];

		for (unsigned int j = 0; j < this->m_size.y; j++)
		{
			this->m_grid[i][j] = other.getCell(sf::Vector2u(i, j));
		}
	}
}


Grid::~Grid()
{
	for (size_t i = 0; i < this->m_size.x; i++)
	{
		delete[] this->m_grid[i];
	}
	delete[] this->m_grid;
}

sf::Vector2u Grid::getSize() const
{
	return this->m_size;
}

Cell Grid::getCell(sf::Vector2u index) const
{
	if (this->isInRange(index))
	{
		return m_grid[index.x][index.y];
	}
}

void Grid::setCell(const Cell& value,sf::Vector2u index)
{
	if (this->isInRange(index))
	{
		m_grid[index.x][index.y] = value;
	}
}

Grid & Grid::operator=(const Grid& other)
{
	this->~Grid();
	this->m_size = other.getSize();
	this->m_grid = new Cell*[this->m_size.x];
	for (size_t i = 0; i < this->m_size.x; i++)
	{
		this->m_grid[i] = new Cell[this->m_size.y];

		for (size_t j = 0; j < this->m_size.y; j++)
		{
			this->m_grid[i][j] = other.getCell(sf::Vector2u(i, j));
		}
	}
	return *this;
}

Cell & Grid::getCell(sf::Vector2u index)
{
	if (this->isInRange(index))
	{
		return m_grid[index.x][index.y];
	}
}

bool Grid::isInRange(sf::Vector2i index) const
{
	return index.x >= 0 && index.y >= 0 && index.x < m_size.x && index.y < m_size.y;
}

bool Grid::isInRange(sf::Vector2u index) const
{
	return index.x >= 0 && index.y >= 0 && index.x < m_size.x && index.y < m_size.y;
}