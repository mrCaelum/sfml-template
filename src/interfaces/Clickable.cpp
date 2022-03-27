#include "interfaces/Clickable.hpp"

Clickable::Clickable(sf::Vector2f const &size, sf::Vector2f const &position)
: _size{size}, _position{position}, _origin{0.0f, 0.0f}
{}

Clickable::Clickable(Clickable const &other)
: _size{other._size}, _position{other._position}, _origin{other._origin}
{}

Clickable &Clickable::operator=(Clickable const &other)
{
	this->_size = other._size;
	this->_position = other._position;
	this->_origin = other._origin;
	return *this;
}

sf::Vector2f const &Clickable::getSize() const
{
	return _size;
}

void Clickable::setSize(sf::Vector2f const &size)
{
	_size = size;
	_update();
}

sf::Vector2f const &Clickable::getPosition() const
{
	return _position;
}

void Clickable::setPosition(sf::Vector2f const &position)
{
	_position = position;
	_update();
}

sf::Vector2f const &Clickable::getOrigin() const
{
	return _origin;
}

void Clickable::setOrigin(sf::Vector2f const &origin)
{
	_origin = origin;
	_update();
}