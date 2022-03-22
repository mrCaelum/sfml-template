#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Animation.hpp"

class Switch : public sf::Drawable
{
private:
	enum MouseState {
		IDLE,
		CLICKED,
		CLICKED_ON
	};

	bool _checked;
	sf::Vector2f _position;
	float _size;
	sf::Color _unchecked_color;
	sf::Color _checked_color;
	float _border_thickness;
	Animation _animation;
	unsigned char _mouse_state;

	sf::RectangleShape _center_border;
	sf::CircleShape _left_background;
	sf::CircleShape _right_background;
	sf::RectangleShape _center_background;
	sf::CircleShape _picker;

	sf::Color _compute_color() const;

public:
	Switch(
		sf::Vector2f const &position,
		const float size,
		sf::Color const &unchecked_color = sf::Color(189, 195, 199),
		sf::Color const &checked_color = sf::Color(52, 152, 219),
		sf::Color const &background_color = sf::Color(236, 240, 241),
		const float border_thickness = 2.0f,
		bool checked = false
	);
	~Switch() = default;

	bool checked() const;
	void check(bool value);

	bool picker_contains(sf::Vector2f const &point) const;
	bool contains(sf::Vector2f const &point) const;

	void update(sf::RenderWindow const &window, const float elapsed_time = 0.0f);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};