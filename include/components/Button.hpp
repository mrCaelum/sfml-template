#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "components/Animation.hpp"
#include "components/RoundedRectangleShape.hpp"

/**
 * @brief A drawable button component. In a square shape.
 */
class Button : public sf::Drawable
{
public:
	/**
	 * @brief The button states.
	 */
	enum State {
		IDLE,
		HOVERED,
		CLICKED,
		RELEASED
	};

	/**
	 * @brief If true, the button switches to its disabled state.
	 * 
	 * @note The button state will still be working.
	 */
	bool disabled;

private:
	RoundedRectangleShape _box;
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
	/**
	 * @brief Construct a new Button object.
	 * 
	 * @param font The text font.
	 * @param text The text string.
	 * @param position The button absolute position.
	 * @param size The button global size.
	 * @param character_size The text size.
	 * @param text_color The text color.
	 * @param background_color The button background color.
	 * @param border_color The button border color.
	 * @param border_thickness The border size.
	 * @param hovered An animation object that will trigger on button hover.
	 * @param clicked An animation object that will trigger on button click.
	 */
	Button(
		sf::Font const &font,
		sf::String const &text,
		sf::Vector2f const &position = {0.0f, 0.0f},
		sf::Vector2f const &size = {200.0f, 40.0f},
		unsigned int const character_size = 24U,
		sf::Color const &text_color = sf::Color{255, 255, 255},
		sf::Color const &background_color = sf::Color{80, 80, 80},
		sf::Color const &border_color = sf::Color{52, 152, 219},
		float const corner_radius = 2.0f,
		float const border_thickness = 1.0f,
		Animation const &hovered = Animation{},
		Animation const &clicked = Animation{}
	);

	/**
	 * @brief Construct a new Button object.
	 * 
	 * @param other The object to copy.
	 */
	Button(Button const &other);

	/**
	 * @brief Destroy the Button object
	 */
	~Button() = default;

	/**
	 * @brief Equal operator.
	 * 
	 * @param other The object to copy.
	 * @return Button&
	 */
	Button &operator=(Button const &other);

	/**
	 * @brief Gets the hovered state.
	 * 
	 * @return true if the mouse hovers above the button.
	 * @return false otherwise.
	 */
	bool hovered() const;

	/**
	 * @brief Gets the clicked state.
	 * 
	 * @return true if the mouse clicked on the button.
	 * @return false otherwise.
	 */
	bool clicked() const;

	/**
	 * @brief Gets the released state.
	 * 
	 * @return true if the mouse has been released on the button.
	 * @return false otherwise.
	 */
	bool released() const;

	/**
	 * @brief Updates the button.
	 * 
	 * @param window The window where the button is drawn.
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

	/**
	 * @brief Draw the button to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};