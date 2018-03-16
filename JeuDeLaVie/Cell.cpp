#include "Cell.h"



Cell::Cell(bool isAlive,sf::Color color)
{
	m_color = color;
	m_alive = isAlive;
}


Cell::~Cell()
{
}

sf::Color Cell::getColor() const
{
	return this->m_color;
}

bool Cell::isAlive() const
{
	return this->m_alive;
}

void Cell::setAlive(bool state)
{
	this->m_alive = state;
}

void Cell::setColor(sf::Color color)
{
	this->m_color = color;
}

Cell & Cell::operator=(const Cell & other)
{
	this->m_alive = other.isAlive();
	this->m_color = other.getColor();
	return *this;
}
