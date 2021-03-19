#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define PI 3.14159265
#define PI_TWO 6.28318530

class Line {

public:
	Line(float Ax, float Ay, float Bx, float By)
	{
		PointsA = sf::Vector2f(Ax, Ay);
		PointsB = sf::Vector2f(Bx, By);
	}

	void display(sf::RenderWindow& thatWindow);
	sf::Vector2f GetPointA();
	sf::Vector2f GetPointB();

	void SetPointA(sf::Vector2f& newPoint);
	void SetPointB(sf::Vector2f& newPoint);

private:
	sf::Vector2f PointsA;
	sf::Vector2f PointsB;
};

class Shadow {

public:
	Shadow(std::vector<Line> s, sf::Vector2f pos, float a)
	{
		segments = s;
		mousepos = pos;
		angle = a;
		moveSpeed = 0.5;
	}

	class Point {

	public:
		Point(sf::Vector2f pos)
		{
			p_pos = pos;
		}

		void display(sf::RenderWindow& thatWindow);
		sf::Vector2f p_pos;
	};
	class IntersectionClass {

	public:
		IntersectionClass(Line ray, Line segments)
		{
			IntersectionVector = getIntersection(ray, segments);
		}

		float param;
		float angle;
		sf::Vector2f IntersectionVector;
		sf::Vector2f getIntersection(Line ray, Line segments);
		
	};

	std::vector<IntersectionClass> intersects;
	std::vector <sf::Vector2f> rays;
	std::vector<float> raysDist;
	std::vector<Line> segments;
	sf::Vector2f mousepos;
	float angle; 
	float moveSpeed;

	float GetDist(sf::Vector2f p, sf::Vector2f inter);
	void debugPoints(sf::RenderWindow& thatWindow);
	void debugLines(sf::RenderWindow& thatWindow);
	void cast();
	void move(sf::Vector2f p);
	void rotate(float _angle);
	
	void draw(sf::RenderWindow& thatWindow);


};
