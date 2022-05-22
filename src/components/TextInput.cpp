#include "components/TextInput.hpp"

TextInput::TextInput(sf::Font const &font, sf::Vector2f const &position, sf::Vector2f const &size, unsigned int const character_size, sf::Color const &text_color, sf::Color const &background_color, sf::Color const &border_color, float const border_thickness, Animation const &hovered, Animation const &clicked)
: _selected{false}, _text{}, _position{position}, _size{size}
{
}

void TextInput::update(float const elapsed_time)
{
}

void TextInput::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}