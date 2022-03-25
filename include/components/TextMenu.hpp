#pragma once

#include <vector>
#include "TextButton.hpp"

/**
 * @brief A drawable menu of clickable text buttons.
 */
class TextMenu : public sf::Drawable
{
private:
	std::vector<TextButton> _buttons;
	sf::Font _font;
	unsigned int _character_size;
	sf::Color _text_color;
	sf::Color _text_outline_color;
	float _outline_thickness;
	TextButton::Origin _origin;
	Animation _hovered;
	Animation _clicked;

public:
	/**
	 * @brief Construct a new Text Menu object.
	 * 
	 * @param font The texts fonts.
	 * @param character_size The texts characters sizes.
	 * @param text_color The texts colors.
	 * @param text_outline_color The texts outline colors.
	 * @param outline_thickness The texts outline thicknesses.
	 * @param origin The texts origins.
	 * @param hovered An animation object targeting texts on mouse hover.
	 * @param clicked An animation object targeting texts on mouse click.
	 */
	TextMenu(
		sf::Font const &font,
		unsigned int const character_size = 30U,
		sf::Color const &text_color = sf::Color::White,
		sf::Color const &text_outline_color = sf::Color::Black,
		float const outline_thickness = 0.0f,
		TextButton::Origin const origin = TextButton::Origin::CENTERED,
		Animation const &hovered = Animation{},
		Animation const &clicked = Animation{}
	);

	/**
	 * @brief Destroy the Text Menu object.
	 */
	~TextMenu() = default;

	/**
	 * @brief Updates the menu buttons states during the event loop.
	 * 
	 * @param window The window where the menu is displayed.
	 * @param event The event object.
	 */
	void updateStates(sf::RenderWindow const &window, sf::Event event);

	/**
	 * @brief Updates the menu.
	 * 
	 * @param window The window where the switch is drawn.
	 * @param elapsed_time The elasped time since the last update.
	 */
	void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

	/**
	 * @brief Adds a button to the menu.
	 * 
	 * @param text The button text.
	 * @param position The button position.
	 */
	void addButton(sf::String const &text, sf::Vector2f const &position);

	/**
	 * @brief Gets a button thanks to its text.
	 * 
	 * @param text The text string of the button.
	 * @return TextButton* that is a pointer on the text button component.
	 */
	TextButton *getButton(sf::String const &text);

	/**
	 * @brief Gets a vector of all button states.
	 * 
	 * @return std::vector<TextButton::State> the vector, containing all button states in the right order.
	 */
	std::vector<TextButton::State> getStates() const;

	/**
	 * @brief Draw the menu to a render target.
	 * 
	 * @param target Render target to draw to.
	 * @param states Current render states.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};