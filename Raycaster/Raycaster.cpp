#include "Raycaster.h"

float DegreeToRadians(float degree) {
	return (degree * PI / 180);
}


void Line::display(sf::RenderWindow& thatWindow)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(PointsA.x, PointsA.y);
	line[1].position = sf::Vector2f(PointsB.x, PointsB.y);
	thatWindow.draw(line);
}

sf::Vector2f Line::GetPointA()
{
	return PointsA;
}

sf::Vector2f Line::GetPointB()
{
	return PointsB;
}

void Line::SetPointA(sf::Vector2f& newPoint)
{
	PointsA = newPoint;
}

void Line::SetPointB(sf::Vector2f& newPoint)
{
	PointsB = newPoint;
}

sf::Vector2f Shadow::IntersectionClass::getIntersection(Line ray, Line segments)
{
	// RAY in parametric: Point + Direction*T1
	float r_px = ray.GetPointA().x;
	float r_py = ray.GetPointA().y;
	float r_dx = ray.GetPointB().x - ray.GetPointA().x;
	float r_dy = ray.GetPointB().y - ray.GetPointA().y;

	// SEGMENT in parametric: Point + Direction*T2
	float s_px = segments.GetPointA().x;
	float s_py = segments.GetPointA().y;
	float s_dx = segments.GetPointB().x - segments.GetPointA().x;
	float s_dy = segments.GetPointB().y - segments.GetPointA().y;

	// Are they parallel? If so, no intersect
	float r_mag = sqrt(r_dx * r_dx + r_dy * r_dy);
	float s_mag = sqrt(s_dx * s_dx + s_dy * s_dy);
	if (r_dx / r_mag == s_dx / s_mag && r_dy / r_mag == s_dy / s_mag) { // Directions are the same.
		return sf::Vector2f();
	}

	// SOLVE FOR T1 & T2
	// r_px+r_dx*T1 = s_px+s_dx*T2 && r_py+r_dy*T1 = s_py+s_dy*T2
	// ==> T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy
	// ==> s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx
	// ==> T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)
	float T2 = (r_dx * (s_py - r_py) + r_dy * (r_px - s_px)) / (s_dx * r_dy - s_dy * r_dx);
	float T1 = (s_px + s_dx * T2 - r_px) / r_dx;

	// Must be within parametic whatevers for RAY/SEGMENT
	if (T1 < 0) return sf::Vector2f();
	if (T2 < 0 || T2>1) return sf::Vector2f();

	// Return the POINT OF INTERSECTION
	param = T1;
	return sf::Vector2f(r_px + r_dx * T1, r_py + r_dy * T1);
}

void Shadow::Point::display(sf::RenderWindow& thatWindow)
{
	sf::CircleShape ball(4);
	ball.setOrigin(2, 2);
	ball.setPosition(p_pos);
	thatWindow.draw(ball);
}

void Shadow::cast()
{

	rays.clear();
	raysDist.clear();
	for (float a = DegreeToRadians(-25); a < DegreeToRadians(25); a += DegreeToRadians(1)) {

			// Calculate dx & dy from angle
			float dx = cosf(a + angle);
			float dy = sinf(a + angle);

			// Ray from center of screen to mouse
			Line ray(mousepos.x, mousepos.y, mousepos.x + dx, mousepos.y + dy);

			// Find CLOSEST intersection
			IntersectionClass closestIntersect(Line(0, 0, 0, 0), Line(0, 0, 0, 0)); closestIntersect.IntersectionVector = sf::Vector2f(); closestIntersect.param = 0; closestIntersect.angle = 0;
			for (int i = 0; i < segments.size(); i++) {
				IntersectionClass intersect(ray, segments[i]);
				if ((intersect.IntersectionVector.x + intersect.IntersectionVector.y) == NULL) continue;
				if (closestIntersect.IntersectionVector == sf::Vector2f() || intersect.param < closestIntersect.param) {
					closestIntersect = intersect;
				}
			}

			//closestIntersect.angle = angle;
			// Add to list of intersects
			rays.push_back(closestIntersect.IntersectionVector);
			
	}

	for (int k = 0; k < rays.size(); k++) {
		raysDist.push_back(GetDist(mousepos, rays[k]));
	}

}

void Shadow::debugPoints(sf::RenderWindow& thatWindow)
{
	for (int j = 0; j < rays.size(); j++) {
		Point points(rays[j]);
		points.display(thatWindow);
	}
}

void Shadow::debugLines(sf::RenderWindow& thatWindow)
{
	for (int j = 0; j < rays.size(); j++) {
		Line laser(mousepos.x, mousepos.y, rays[j].x, rays[j].y);
		laser.display(thatWindow);
	}
}

void Shadow::move(sf::Vector2f p)
{

	mousepos = p;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	//	//std::cout << "left (" << mousepos.y << ") \n";
	//	mousepos.x -= moveSpeed;
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	//	//std::cout << "right (" << mousepos.y << ") \n";
	//	mousepos.x += moveSpeed;
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	//	//std::cout << "up (" << mousepos.y << ") \n";
	//	mousepos.y -= moveSpeed;
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	//	//std::cout << "down (" << mousepos.y << ") \n";
	//	mousepos.y += moveSpeed;
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//std::cout << "rotate left (" << this->angle << ") \n";
		rotate(-0.5);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//std::cout << "rotate right (" << this->angle << ") \n";
		rotate(0.5);
	}

}


void Shadow::rotate(float _angle)
{

	this->angle += DegreeToRadians(_angle);

}


float Map(float value, float minRange, float maxRange, float minDomain, float maxDomain) {
	return minDomain + (maxDomain - minDomain) * (value - minRange) / (maxRange - minRange);
}

void Shadow::draw(sf::RenderWindow& thatWindow)
{

	
	int w = 680 / raysDist.size();
	static int heightOfScene = 360;

	for (size_t i = 0; i < raysDist.size(); i++) {

		float c = Map(raysDist[i], 0, 640, 255, 0);
		float h = Map(raysDist[i], 0, 640, 360, 0);

		sf::RectangleShape a;
		a.setPosition(sf::Vector2f(i * w, 720 - 180));
		a.setSize(sf::Vector2f(w, h));
		a.setOrigin(sf::Vector2f(a.getSize().x / 2, a.getSize().y / 2));
		a.setFillColor(sf::Color(c,59,125));
		thatWindow.draw(a);

	}

}

float Shadow::GetDist(sf::Vector2f p, sf::Vector2f inter)
{
	// Calculating distance 
	return sqrt(pow(inter.x - p.x, 2) + pow(inter.y - p.y, 2) * 1.0);
}