#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <Windows.h>
#include "Application.h"

#define WIDTH 1920
#define HEIGHT 1080
#define K 2
#define Row 1920 / K
#define Col 1080 / K
#define PROBA 0.05


void printGrid(const Grid& grid);

#ifndef DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif // !DEBUG



#define START_PAUSE true


int main(int argv, char **argc)
{
	bool pause = START_PAUSE;
	unsigned long long time = GetTickCount64();
	unsigned long long time2 = GetTickCount64();
	sf::Font font;
	if (!font.loadFromFile("C:\\Users\\Vincent\\Source\\Repos\\JeuDeLaVie\\arial.ttf"))
	{
		// erreur...
		exit(EXIT_FAILURE);
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(0.1);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Jeu de la vie", sf::Style::Fullscreen);
	Application app(&window,sf::Vector2u(Row, Col));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			app.countAlive();
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) pause = !pause;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					app.resetGrid();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{
					app.fillGrid(PROBA);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				{
					sf::Color color = app.randomColor();
					unsigned int i = app.getCurrentGrid().getSize().y / 2;
					for (unsigned int j = 0; j < app.getCurrentGrid().getSize().x; j++)
					{
						app.getCurrentGrid().getCell(sf::Vector2u(j, i)) = Cell(true, color);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				{
					sf::Color color = app.randomColor();
					unsigned int i = app.getCurrentGrid().getSize().x / 2;
					for (unsigned int j = 0; j < app.getCurrentGrid().getSize().y; j++)
					{
						app.getCurrentGrid().getCell(sf::Vector2u(i, j)) = Cell(true, color);
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					sf::Color color = app.randomColor();
					while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						app.createCell(sf::Mouse::getPosition(),color);
						window.clear(DEAD);
						app.display();
						window.draw(text);
						window.display();
					}
					while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						app.eraseCell(sf::Mouse::getPosition());
						window.clear(DEAD);
						app.display();
						window.draw(text);
						window.display();
					}
				}
				break;
			default:
				break;
			}
		}

#ifdef DEBUG
		if(!pause)
			std::cout << "Etape : " << app.getEtape() << std::endl;
#endif // DEBUG

		
		if (!pause) app.nextGrid();
		double speed;
		if (time != GetTickCount64() && !pause)
			speed = 1000 / (GetTickCount64() - time);
		else
			speed = 0;
		time = GetTickCount64();
		if (GetTickCount64() - time2 > 250)
		{
			time2 = GetTickCount64();
			std::stringstream ss;
			ss << " Cycles : " << app.getEtape() << std::endl;
			if (!pause)
				ss << " Speed : " << speed << " Cycle/Second" << std::endl;
			else
				ss << " Paused" << std::endl;
			ss << " Alive cell : " << app.getAlive();
			
			text.setString(ss.str());
		}
		window.clear(DEAD);
		app.display();
		window.draw(text);
		window.display();
	}
	return 0;
}

void printGrid(const Grid& grid)
{
	sf::Vector2u size = grid.getSize();
	for (unsigned int i = 0; i < size.x; i++)
	{
		for (unsigned int j = 0; j < size.y; j++)
		{
			if (grid.getCell(sf::Vector2u(i, j)).isAlive())
			{
				std::cout << "1" << "";
			}
			else
			{
				std::cout << "0" << "";
			}
		}
		std::cout << std::endl;
	}
}
