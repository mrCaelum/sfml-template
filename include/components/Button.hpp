#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

class Button : public sf::Drawable
{
public:
	enum State {
		IDLE,
		HOVERED,
		CLICKED,
		RELEASED
	};

	bool disabled;

private:
	sf::RectangleShape _box;
	sf::Text _text;
	sf::Vector2f _position;
	sf::Color _text_color;
	sf::Color _background_color;
	sf::Color _border_color;
	Animation _hovered;
	Animation _clicked;
	float _elapsed_time;
	State _state;

public:
	Button(
		sf::Font const &font,
		sf::String const &text,
		sf::Vector2f const &position = {0.0f, 0.0f},
		sf::Vector2f const &size = {200.0f, 40.0f},
		unsigned int const character_size = 24U,
		sf::Color const &text_color = sf::Color{255, 255, 255},
		sf::Color const &background_color = sf::Color{80, 80, 80},
		sf::Color const &border_color = sf::Color{52, 152, 219},
		float const border_thickness = 1.0f,
		Animation const &hovered = Animation{},
		Animation const &clicked = Animation{}
	);
	Button() = delete;
	~Button() = default;

	bool hovered() const;
	bool clicked() const;
	bool released() const;

	void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};