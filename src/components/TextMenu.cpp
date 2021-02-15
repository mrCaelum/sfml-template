#include "TextMenu.hpp"

TextMenu::TextMenu(sf::Font const &font, unsigned int const character_size, sf::Color const &text_color, sf::Color const &text_outline_color, float const outline_thickness, TextButton::Origin const origin, TextAnimation const &hovered, TextAnimation const &clicked)
: _buttons{}, _font{font}, _character_size{character_size}, _text_color{text_color}, _text_outline_color{text_outline_color}, _outline_thickness{outline_thickness}, _origin{origin}, _hovered{hovered}, _clicked{clicked}
{}

void TextMenu::updateStates(sf::RenderWindow const &window, sf::Event event)
{
    for (std::vector<TextButton>::iterator it = _buttons.begin(); it != _buttons.end(); ++it) {
        it->updateState(window, event);
    }
}

void TextMenu::update(sf::RenderWindow const &window, float const elapsed_time)
{
    for (std::vector<TextButton>::iterator it = _buttons.begin(); it != _buttons.end(); ++it) {
        it->update(window, elapsed_time);
    }
}

void TextMenu::addButton(sf::String const &text, sf::Vector2f const &position)
{
    _buttons.emplace_back(text, _font, position, _character_size, _text_color, _text_outline_color, _outline_thickness, _origin, _hovered, _clicked);
}

TextButton *TextMenu::getButton(sf::String const &text)
{
    for (std::vector<TextButton>::iterator it = _buttons.begin(); it != _buttons.end(); ++it) {
        if (it->getString() == text)
            return &*it;
    }
    return nullptr;
}

void TextMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (std::vector<TextButton>::const_iterator it = _buttons.begin(); it != _buttons.end(); ++it) {
        target.draw(*it, states);
    }
}