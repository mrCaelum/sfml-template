#include "TextDropdown.hpp"

TextDropdownElement::TextDropdownElement(sf::String const &text)
: _text{}
{
    _text.setString(text);
}

void TextDropdownElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_text, states);
}

TextDropdown::TextDropdown(sf::Font const &font, sf::String const &placeholder, sf::Vector2f const &position, sf::Vector2f const &size, unsigned int character_size, sf::Color primary_color, sf::Color background_color)
: _position{position}, _box{}, _arrow{size.y / 8.0f, 3}, _selectedText{}, _frame{}
{
    _box.setPosition(_position);
    _box.setSize(size);
    _box.setFillColor(background_color);
    _box.setOutlineColor(primary_color);
    _box.setOutlineThickness(2.0f);

    _selectedText.setFont(font);
    _selectedText.setString(placeholder);
    _selectedText.setOrigin({0.0f, _selectedText.getGlobalBounds().height / 2.0f});
    _selectedText.setPosition({_position.x + 10.0f, _position.y + size.y / 2.0f});
    _selectedText.setFillColor(sf::Color(200, 200, 200));
    _selectedText.setCharacterSize(character_size);

    _arrow.setFillColor(primary_color);
    _arrow.setOrigin({_arrow.getRadius(), _arrow.getRadius()});
    _arrow.setPosition({position.x + size.x - _arrow.getRadius() * 4.0f, position.y + size.y / 2.0f});
    _arrow.rotate(180.0f);
}

void TextDropdown::update(sf::RenderWindow const &window, float const elapsed_time)
{}

void TextDropdown::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_box, states);
    target.draw(_selectedText, states);
    target.draw(_arrow, states);
}