#include "Application.h"


Application::Application(sf::RenderTarget *target,sf::Vector2u size) : m_grid(size)
{
	m_target = target;
	m_size = size;
	m_etape = 0;
	m_alive_count = 0;
}

Application::Application(sf::RenderTarget *target,sf::Vector2u size, double proba): m_grid(size)
{
	m_etape = 0;
	m_target = target;
	m_size = size;
	createGrid(proba);
}

Application::Application(sf::RenderTarget *target, const Grid & grid) : m_grid(grid)
{
	m_etape = 0;
	m_target = target;
	m_size = grid.getSize();
}

Application::~Application()
{
}

std::vector<Grid> Application::trajectory(size_t n)
{
	std::vector<Grid> rep;
	rep.push_back(this->m_grid);
	for (size_t i = 0; i < n; i++)
	{
		this->nextGrid();
		rep.push_back(this->m_grid);
	}
	return rep;
}

Grid & Application::getCurrentGrid()
{
	return this->m_grid;
}

sf::Vector2u Application::getSize() const
{
	return m_size;
}

size_t Application::getEtape() const
{
	return m_etape;
}

void Application::nextGrid()
{
	this->m_etape++;
	Grid temp = m_grid;
	for (unsigned int i = 0; i < this->m_size.x; i++)
	{
		for (unsigned int j = 0; j < this->m_size.y; j++)
		{
			this->m_grid.setCell(this->checkCell(sf::Vector2u(i, j), temp),sf::Vector2u(i,j));
		}
	}
}

void Application::setGrid(Grid& other)
{
	m_etape = 0;
	m_size = other.getSize();
	m_grid = other;
	countAlive();
	return;
}

void Application::resetGrid()
{
	sf::Vector2u size = this->m_grid.getSize();
	this->m_grid = Grid(size);
	this->m_etape = 0;
	m_alive_count = 0;
}

void Application::fillGrid(double proba)
{
	this->createGrid(proba);
}

void Application::display() const
{
	sf::Vector2u screen_size = m_target->getSize();
	for (unsigned int i = 0; i < this->m_size.x; i++)
	{
		for (unsigned int j = 0; j < this->m_size.y; j++)
		{
			if (this->m_grid.getCell(sf::Vector2u(i, j)).isAlive())
			{
				sf::VertexArray vertex(sf::PrimitiveType::Quads, 4);
				sf::Vector2f position;
				//First point
				position.x = (i + 1)*(screen_size.x / this->m_size.x);
				position.y = (j + 1)*(screen_size.y / this->m_size.y);
				vertex[0] = sf::Vertex(position, this->m_grid.getCell(sf::Vector2u(i, j)).getColor());
				//Second point
				position.x = (i + 1)*(screen_size.x / this->m_size.x);
				position.y = j*(screen_size.y / this->m_size.y);
				vertex[1] = sf::Vertex(position, this->m_grid.getCell(sf::Vector2u(i, j)).getColor());
				//Third point
				position.x = i*(screen_size.x / this->m_size.x);
				position.y = j*(screen_size.y / this->m_size.y);
				vertex[2] = sf::Vertex(position, this->m_grid.getCell(sf::Vector2u(i, j)).getColor());
				//Last point
				position.x = i*(screen_size.x / this->m_size.x);
				position.y = (j + 1)*(screen_size.y / this->m_size.y);
				vertex[3] = sf::Vertex(position, this->m_grid.getCell(sf::Vector2u(i, j)).getColor());
				//Draw the square
				m_target->draw(vertex);
			}			
		}
	}

}

void Application::countAlive()
{
	m_alive_count = 0;
	for (unsigned int i = 0; i < this->m_size.x; i++)
	{
		for (unsigned int j = 0; j < this->m_size.y; j++)
		{
			if (this->m_grid.getCell(sf::Vector2u(i, j)).isAlive())
			{
				m_alive_count += 1;
			}
		}
	}
}

void Application::eraseCell(sf::Vector2i mouse)
{
	sf::Vector2u screen_size = this->m_target->getSize();
	sf::Vector2u grid_size = this->m_grid.getSize();
	sf::Vector2u position;
	position.x = unsigned int(mouse.x * grid_size.x / screen_size.x);
	position.y = unsigned int(mouse.y * grid_size.y / screen_size.y);
	this->m_grid.getCell(position).setAlive(false);
#ifdef DEBUG
	std::cout << "Eraseing" << std::endl;
	std::cout << "Position mouse : x = " << mouse.x << ", y = " << mouse.y << std::endl;
	std::cout << "Corresponding case : x = " << position.x << ", y = " << position.y << std::endl;
#endif // DEBUG

}

void Application::createCell(sf::Vector2i mouse,sf::Color color)
{
	sf::Vector2u screen_size = this->m_target->getSize();
	sf::Vector2u grid_size = this->m_grid.getSize();
	sf::Vector2u position;
	position.x = unsigned int(mouse.x * grid_size.x / screen_size.x);
	position.y = unsigned int(mouse.y * grid_size.y / screen_size.y);
	this->m_grid.getCell(position).setAlive(true);
	this->m_grid.getCell(position).setColor(color);
#ifdef DEBUG
	std::cout << "Creating -> x=" << mouse.x << ",y=" << mouse.y << std::endl;
	std::cout << "Position mouse : x = " << mouse.x << ", y = " << mouse.y << std::endl;
	std::cout << "Corresponding case : x = " << position.x << ", y = " << position.y << std::endl;
#endif // DEBUG

}

unsigned int Application::getAlive() const
{
	return m_alive_count;
}

sf::Color Application::randomColor() const
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255, 255);
}

Cell Application::checkCell(sf::Vector2u index,const Grid& grid) const
{
	std::vector<COLOR> color;
	size_t alive = 0;
	for (int i = (int)index.x - 1; i <= (int)index.x + 1; i++)
	{
		for (int j = (int)index.y - 1; j <= (int)index.y + 1; j++)
		{
			if ((i != index.x || j != index.y) && grid.isInRange(sf::Vector2u(i,j)))
			{
				if (grid.getCell(sf::Vector2u(i, j)).isAlive())
				{
					alive += 1;
					bool test = false;
					for (auto p : color)
					{
						if (p.color == grid.getCell(sf::Vector2u(i, j)).getColor())
						{
							test = true;
							break;
							p.count += 1;
						}
					}
					if (!test)
					{
						COLOR tmp;
						tmp.color = grid.getCell(sf::Vector2u(i, j)).getColor();
						tmp.count = 1;
						color.push_back(tmp);
					}
				}
			}
		}
	}
	bool isAlive = (!grid.getCell(index).isAlive() && alive == 3) || (grid.getCell(index).isAlive() && (alive == 2 || alive == 3));
	COLOR max;
	max.count = -1;
	for (auto &i : color)
	{
		if (i.count > max.count)
		{
			max.count = i.count;
			max.color = i.color;
		}
	}
	return Cell(isAlive, max.color);
}

void Application::createGrid(double proba)
{
	std::srand(unsigned int(std::time(nullptr)));
	for (unsigned int i=0; i < m_size.x; i++)
	{
		for (unsigned int j=0; j < m_size.y; j++)
		{
			if (std::rand() < (int)(RAND_MAX*proba))
			{
				this->m_grid.getCell(sf::Vector2u(i,j)).setAlive(true); 
				this->m_grid.getCell(sf::Vector2u(i,j)).setColor(this->randomColor());
				m_alive_count += 1;
			}
		}

	}
}
