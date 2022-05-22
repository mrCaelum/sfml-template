#pragma once

#include <SFML/Graphics/Drawable.hpp>

class Clickable : public sf::Drawable
{
private:
	sf::Vector2f _size;
	sf::Vector2f _position;
	sf::Vector2f _origin;

protected:
	Clickable(sf::Vector2f const &size = {0.0f, 0.0f}, sf::Vector2f const &position = {0.0f, 0.0f});
	Clickable(Clickable const &other);
	Clickable &operator=(Clickable const &other);

public:
	~Clickable() = default;

	sf::Vector2f const &getSize() const;
	void setSize(sf::Vector2f const &size);

	sf::Vector2f const &getPosition() const;
	void setPosition(sf::Vector2f const &position);

	sf::Vector2f const &getOrigin() const;
	void setOrigin(sf::Vector2f const &origin);

	virtual bool contains(sf::Vector2f const &point) const = 0;

private:
	virtual void _update() = 0;
};