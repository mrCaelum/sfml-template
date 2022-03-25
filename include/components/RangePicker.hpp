#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

/**
 * @brief A drawable range picker component.
 */
class RangePicker : public sf::Drawable
{
private:
	unsigned int _range;
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::Color _color;
	unsigned int _value;
	sf::CircleShape _point;
	sf::RectangleShape _line;
	sf::CircleShape _left_bound;
	sf::CircleShape _right_bound;
	sf::RectangleShape _borders;
	bool _selected;

public:
	/**
	 * @brief Construct a new Range Picker object
	 * 
	 * @param range The number of steps.
	 * @param position The absolute position.
	 * @param size The global size.
	 * @param color The main color.
	 * @param bar_color The bar color.
	 */
	RangePicker(
		unsigned int range = 10u,
		sf::Vector2f position = {0.0f, 0.0f},
		sf::Vector2f size = {300.0f, 15.0f},
		sf::Color color = sf::Color(52, 152, 219),
		sf::Color bar_color = sf::Color(236, 240, 241)
	);

	/**
	 * @brief Construct a new Range Picker object.
	 * 
	 * @param other The object to copy.
	 */
	RangePicker(RangePicker const &other);

	/**
	 * @brief Destroy the Range Picker object
	 */
	~RangePicker() = default;

	/**
	 * @brief Equal operator.
	 * 
	 * @param other The object to copy.
	 * @return RangePicker& 
	 */
	RangePicker &operator=(RangePicker const &other);

	/**
	 * @brief Get the value in the range.
	 * 
	 * @return unsigned int the value between 0 and the total number of steps.
	 */
	unsigned int getValue() const;

	/**
	 * @brief Get the actual position of the object.
	 * 
	 * @return sf::Vector2f const& the actual position on the screen.
	 */
	sf::Vector2f const &getPosition() const;

	/**
	 * @brief Set a new absolute position for the object.
	 * 
	 * @param position the new position.
	 */
	void setPosition(sf::Vector2f const &position);

	/**
	 * @brief Check if the given point is graphically contained in the object.
	 * 
	 * @param point the point to check.
	 * @return true id the point is cointains in the global bounds of the object.
	 * @return false otherwise.
	 */
	bool contains(sf::Vector2f const &point) const;

	/**
	 * @brief Updates the object
	 * 
	 * @param window The window where the object is drawn.
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(sf::RenderWindow const &window);

	/**
	 * @brief Draw the object to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};