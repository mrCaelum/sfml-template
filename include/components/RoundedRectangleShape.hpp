#pragma once

#include <SFML/Graphics/Shape.hpp>

class RoundedRectangleShape : public sf::Shape
{
public:
	explicit RoundedRectangleShape(sf::Vector2f const &size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0);

	void setSize(sf::Vector2f const &size);

	sf::Vector2f const &getSize() const;

	void setCornersRadius(float radius);

	float getCornersRadius() const;

	void setCornerPointCount(unsigned int count);

	virtual std::size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t index) const;

private:
	sf::Vector2f _size;
	float _radius;
	unsigned int _cornerPointCount;
};