#include <cmath>
#include "RoundedRectangleShape.hpp"

RoundedRectangleShape::RoundedRectangleShape(sf::Vector2f const &size, float radius, unsigned int cornerPointCount)
: _size{size}, _radius{radius}, _cornerPointCount{cornerPointCount}
{
	update();
}

void RoundedRectangleShape::setSize(sf::Vector2f const &size)
{
	_size = size;
	update();
}

sf::Vector2f const &RoundedRectangleShape::getSize() const
{
	return _size;
}

void RoundedRectangleShape::setCornersRadius(float radius)
{
	_radius = radius;
	update();
}

float RoundedRectangleShape::getCornersRadius() const
{
	return _radius;
}

void RoundedRectangleShape::setCornerPointCount(unsigned int count)
{
	_cornerPointCount = count;
	update();
}

std::size_t RoundedRectangleShape::getPointCount() const
{
	return _cornerPointCount * 4u;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
{
	if (index >= _cornerPointCount * 4u)
		return sf::Vector2f{0,0};

	float deltaAngle = 90.0f / (_cornerPointCount - 1);
	sf::Vector2f center;
	unsigned int centerIndex = index / _cornerPointCount;
	static const float pi = 3.141592654f;

	switch(centerIndex) {
		case 0: center.x = _size.x - _radius; center.y = _radius; break;
		case 1: center.x = _radius; center.y = _radius; break;
		case 2: center.x = _radius; center.y = _size.y - _radius; break;
		case 3: center.x = _size.x - _radius; center.y = _size.y - _radius; break;
	}

	return sf::Vector2f(_radius * cos(deltaAngle*(index-centerIndex)*pi/180)+center.x, -_radius * sin(deltaAngle*(index-centerIndex)*pi/180)+center.y);
}