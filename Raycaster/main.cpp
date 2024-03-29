#include <iostream>
#include <SFML/Graphics.hpp>
#include "Raycaster.h"

using namespace std;
using namespace sf;

vector<Line> segments;

void drawSegments(sf::RenderWindow& thatWindow) {
	for (int i = 0; i < segments.size(); i++) {
		segments[i].display(thatWindow);
	}
}

int main()
{
	//segments
	{
		//Window Border
		segments.push_back(Line(0, 0, 640, 0));
		segments.push_back(Line(640, 0, 640, 360));
		segments.push_back(Line(640, 360, 0, 360));
		segments.push_back(Line(0, 360, 0, 0));
		// Ploy #1
		segments.push_back(Line(100, 150, 120, 50));
		segments.push_back(Line(120, 50, 200, 80));
		segments.push_back(Line(200, 80, 140, 210));
		segments.push_back(Line(140, 210, 100, 150));
		// Ploy #2
		segments.push_back(Line(100, 200, 120, 250));
		segments.push_back(Line(120, 250, 60, 300));
		segments.push_back(Line(60, 300, 100, 200));
		// Ploy #3
		segments.push_back(Line(200, 260, 220, 150));
		segments.push_back(Line(220, 150, 300, 200));
		segments.push_back(Line(300, 200, 350, 320));
		segments.push_back(Line(350, 320, 200, 260));
		// Ploy #4
		segments.push_back(Line(340, 60, 360, 40));
		segments.push_back(Line(360, 40, 370, 70));
		segments.push_back(Line(370, 70, 340, 60));
		// Ploy #5
		segments.push_back(Line(450, 190, 560, 170));
		segments.push_back(Line(560, 170, 540, 270));
		segments.push_back(Line(540, 270, 430, 290));
		segments.push_back(Line(430, 290, 450, 190));
		// Play #6
		segments.push_back(Line(400, 95, 580, 50));
		segments.push_back(Line(580, 50, 480, 150));
		segments.push_back(Line(480, 150, 400, 95));
	}

	sf::ContextSettings settings; settings.antialiasingLevel = 16; settings.depthBits = 24;
	sf::RenderWindow window(sf::VideoMode(640, 720), "2D Shadows", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	Shadow main(segments, sf::Vector2f(320, 180), 0);
	sf::Vector2f position(250, 100);
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				if (event.key.code == sf::Keyboard::Down)
					position.y += 2.5;

				if (event.key.code == sf::Keyboard::Up)
					position.y -= 2.5;


				if (event.key.code == sf::Keyboard::Right)
					position.x += 2.5;

				if (event.key.code == sf::Keyboard::Left)
					position.x -= 2.5;

			default:
				break;
			}

		}

		window.clear();

		main.cast();
		main.debugLines(window);
		main.move(position);


		main.draw(window);

		drawSegments(window);

		window.display();
	}

	return 0;
}