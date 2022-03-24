#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Animation.hpp"

/**
 * @brief A drawable switch component.
 */
class Switch : public sf::Drawable
{
private:
	bool _checked;
	bool _clicked;
	sf::Vector2f _position;
	float _size;
	sf::Color _unchecked_color;
	sf::Color _checked_color;
	float _border_thickness;
	Animation _animation;

	sf::RectangleShape _center_border;
	sf::CircleShape _left_background;
	sf::CircleShape _right_background;
	sf::RectangleShape _center_background;
	sf::CircleShape _picker;

	sf::Color _compute_color() const;

public:
	/**
	 * @brief Construct a new Switch object.
	 * 
	 * @param position The absolute position.
	 * @param size The global size.
	 * @param unchecked_color The primary color when the switch is unchecked.
	 * @param checked_color The primary color when the switch is checked.
	 * @param background_color The background color.
	 * @param border_thickness The border size.
	 * @param checked If the switch is checked by default.
	 */
	Switch(
		sf::Vector2f const &position,
		const float size,
		sf::Color const &unchecked_color = sf::Color(189, 195, 199),
		sf::Color const &checked_color = sf::Color(52, 152, 219),
		sf::Color const &background_color = sf::Color(236, 240, 241),
		const float border_thickness = 2.0f,
		bool checked = false
	);

	Switch() = delete;

	/**
	 * @brief Destroy the Switch object
	 */
	~Switch() = default;

	/**
	 * @brief Gets the checked state of the switch.
	 * 
	 * @return true if the switch is checked.
	 * @return false if the switch is unchecked.
	 */
	bool checked() const;

	/**
	 * @brief Manually check the switch.
	 * 
	 * @param value The new switch position. If true, the switch will be checked. If false, the switch will be unchecked.
	 */
	void check(bool value);

	/**
	 * @brief Checks if the point is contained in the picker.
	 * 
	 * @param point The point to check.
	 * @return true if the point is graphically contained in the picker.
	 * @return false otherwise.
	 */
	bool picker_contains(sf::Vector2f const &point) const;

	/**
	 * @brief Checks if the point is contained in the switch.
	 * 
	 * @param point The point to check.
	 * @return true if the point is graphically contained in the switch.
	 * @return false otherwise.
	 */
	bool contains(sf::Vector2f const &point) const;

	/**
	 * @brief Updates the switch.
	 * 
	 * @param window The window where the switch is drawn.
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(sf::RenderWindow const &window, const float elapsed_time = 0.0f);

	/**
	 * @brief Draw the switch to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};