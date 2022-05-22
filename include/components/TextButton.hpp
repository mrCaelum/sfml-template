#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "components/Animation.hpp"

/**
 * @brief A drawable text button component.
 */
class TextButton : public sf::Drawable
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
	 * @brief The button origin. Will be where any translation animation starts.
	 */
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
	/**
	 * @brief Construct a new Text Button object.
	 * 
	 * @param text The text string.
	 * @param font The text font.
	 * @param position The global postion.
	 * @param size The text size.
	 * @param color The text color.
	 * @param outline_color The text outline color.
	 * @param outline_thickness The text outline thickness.
	 * @param origin The object origin.
	 * @param hovered An animation object that triggers on mouse hover.
	 * @param clicked An animation object that triggers on mouse click.
	 */
	TextButton(
		sf::Font const &font,
		sf::String const &text,
		sf::Vector2f const &position = {0.0f, 0.0f},
		unsigned int const size = 30U,
		sf::Color const &color = sf::Color::White,
		sf::Color const &outline_color = sf::Color::Black,
		float const outline_thickness = 0.0f,
		Origin const origin = Origin::CENTERED,
		Animation const &hovered = Animation{},
		Animation const &clicked = Animation{}
	);

	/**
	 * @brief Destroy the Text Button object.
	 */
	~TextButton() = default;

	/**
	 * @brief Updates the button state during the event loop.
	 * 
	 * @param window The window where the button is drawn.
	 * @param event The event object.
	 */
	void updateState(sf::Event event);

	/**
	 * @brief Gets the state of the object.
	 * 
	 * @return State enum.
	 */
	State getState() const;

	/**
	 * @brief Updates the object.
	 * 
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(float const elapsed_time = 0.0f);

	/**
	 * @brief Gets the text string.
	 * 
	 * @return sf::String const& the text string.
	 */
	sf::String const &getString() const;

	/**
	 * @brief Gets the position of the object.
	 * 
	 * @return sf::Vector2f const& the global position.
	 */
	sf::Vector2f const &getPosition() const;

	/**
	 * @brief Sets a new global position to the object.
	 * 
	 * @param position the new position.
	 */
	void setPosition(sf::Vector2f const &position);

	/**
	 * @brief Sets the origin of the object.
	 * 
	 * @note The origin is used during translation animations.
	 * 
	 * @param origin the origin enum.
	 */
	void setOrigin(Origin const origin);

	/**
	 * @brief Draw the switch to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};