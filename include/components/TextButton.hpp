#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

class TextButton : public sf::Drawable
{
public:
	enum State {
		IDLE,
		HOVERED,
		CLICKED,
		RELEASED
	};
	enum Origin {
		CENTERED,
		LEFT,
		TOP,
		RIGHT,
		BOTTOM,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

private:
	sf::Text _text;
	sf::Vector2f _position;
	Animation _hovered;
	Animation _clicked;
	float _elapsed_time;
	State _state;

public:
	TextButton(
		sf::String const &text,
		sf::Font const &font,
		sf::Vector2f const &position = {0.0f, 0.0f},
		unsigned int const size = 30U,
		sf::Color const &color = sf::Color::White,
		sf::Color const &outline_color = sf::Color::Black,
		float const outline_thickness = 0.0f,
		Origin const origin = Origin::CENTERED,
		Animation const &hovered = Animation{},
		Animation const &clicked = Animation{}
	);
	TextButton() = delete;
	~TextButton() = default;

	void updateState(sf::RenderWindow const &window, sf::Event event);
	State getState() const;
	void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

	sf::String const &getString() const;

	sf::Vector2f const &getPosition() const;
	void setPosition(sf::Vector2f const &position);

	void setOrigin(Origin const origin);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};