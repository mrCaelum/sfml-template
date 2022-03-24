#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

/**
 * @brief A drawable text element part of a text dropdown.
 * 
 * @note Need to be used inside of a text dropdown.
 */
class TextDropdownElement : public sf::Drawable
{
private:
	sf::Vector2f _size;
	sf::Text _text;
	sf::RectangleShape _box;

public:
	/**
	 * @brief Construct a new Text Dropdown Element object.
	 * 
	 * @param font The text font.
	 * @param text The text string.
	 * @param size The object size.
	 * @param character_size The text size.
	 */
	TextDropdownElement(
		sf::Font const &font,
		sf::String const &text,
		sf::Vector2f const &size,
		unsigned int character_size
	);

	/**
	 * @brief Destroy the Text Dropdown Element object.
	 */
	~TextDropdownElement() = default;

	/**
	 * @brief Gets the text string.
	 * 
	 * @return sf::String the text string.
	 */
	sf::String getValue() const;

	/**
	 * @brief Set a new postion to the object.
	 * 
	 * @param position The new position to apply.
	 */
	void setPosition(sf::Vector2f const &position);

	/**
	 * @brief Updates the object and check if the object is selected.
	 * 
	 * @param mouse_position The actual mouse position, to see if the object is selected.
	 * @return true if the mouse is contained in the object global bounds.
	 * @return false otherwise.
	 */
	bool update(sf::Vector2f const &mouse_position);

	/**
	 * @brief Draw the object to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


/**
 * @brief A drawable text dropdown component.
 */
class TextDropdown : public sf::Drawable
{
public:
	/**
	 * @brief The object states.
	 */
	enum State {
		IDLE,
		CLICKED,
		RELEASED,
		DISABLED
	};

	/**
	 * @brief Puts the object in disabled state if true.
	 */
	bool disabled;

private:
	sf::Font _font;
	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::Vector2f _dropdown_size;
	unsigned int _character_size;
	sf::Color _primary_color;
	sf::Color _background_color;
	sf::RectangleShape _box;
	sf::CircleShape _arrow;
	sf::Text _selectedText;
	sf::RenderTexture _texture_frame;
	sf::Sprite _frame;
	std::vector<TextDropdownElement> _elements;
	Animation _arrow_clicked;
	State _state;
	bool _unwrapped;
	bool _changed;

public:
	/**
	 * @brief Construct a new Text Dropdown object.
	 * 
	 * @param font The text font.
	 * @param placeholder The dropdown placeholder / default value.
	 * @param position The absolute position.
	 * @param size The global size.
	 * @param dropdown_size The unwraped dropdown size.
	 * @param character_size The text size.
	 * @param primary_color The primary color.
	 * @param background_color The background color.
	 * @param arrow_clicked An animation object that targets the arrow on dropdown clicked.
	 */
	TextDropdown(
		sf::Font const &font,
		sf::String const &placeholder,
		sf::Vector2f const &position,
		sf::Vector2f const &size = {200.0f, 40.0f},
		sf::Vector2f const &dropdown_size = {200.0f, 200.0f},
		unsigned int character_size = 20U,
		sf::Color const &primary_color = sf::Color{52, 152, 219},
		sf::Color const &background_color = sf::Color{80, 80, 80},
		Animation const &arrow_clicked = Animation{Animation::Type::NEGATIVE_ROTATION, 0.1f, 60.0f}
	);

	TextDropdown() = delete;

	/**
	 * @brief Destroy the Text Dropdown object.
	 */
	~TextDropdown() = default;

	/**
	 * @brief Adds a dropdown element.
	 * 
	 * @param text The element value, as a string.
	 */
	void addElement(sf::String const &text);

	/**
	 * @brief Gets the changed state.
	 * 
	 * @return true when the dropdown value have been changed.
	 * @return false otherwise.
	 */
	bool changed();

	/**
	 * @brief Gets the unwrapped state.
	 * 
	 * @return true when the dropdown is unwrapped.
	 * @return false otherwise.
	 */
	bool unwrapped() const;

	/**
	 * @brief Get the value of the selected element.
	 * 
	 * @return sf::String the selected element text.
	 */
	sf::String getValue() const;

	/**
	 * @brief Forcefully set the current value of the dropdown.
	 * 
	 * @param text The new value to set.
	 */
	void setValue(sf::String const &text);

	/**
	 * @brief Updates the dropdown.
	 * 
	 * @param window The window where the dropdown is drawn.
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

	/**
	 * @brief Draw the dropdown to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};