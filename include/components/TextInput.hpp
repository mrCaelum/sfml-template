#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

/**
 * @brief A drawable text input component.
 */
class TextInput : public sf::Drawable
{
private:
	bool _selected;
	sf::Text _text;
	sf::Vector2f _position;
	sf::Vector2f _size;

public:
	TextInput(
		sf::Font const &font,
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

	TextInput() = delete;

	/**
	 * @brief Destroy the Text Input object.
	 */
	~TextInput() = default;

	/**
	 * @brief Updates the object.
	 * 
	 * @param window The window where the object is drawn.
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

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
	// void setOrigin(Origin const origin);

	/**
	 * @brief Draw the switch to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};