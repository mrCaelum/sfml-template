#include "Button.hpp"

Button::Button(sf::String const &text, sf::Font const &font, sf::Vector2f const &position, sf::Vector2f const &size, unsigned int const character_size, sf::Color const &color, sf::Color const &outline_color, float const outline_thickness, Animation const &hovered, Animation const &clicked)
: _box{}, _text{}, _position{position}, _hovered{hovered}, _clicked{clicked}, _elapsed_time{0.0f}, _state{State::IDLE}
{
    _text.setFont(font);
    _text.setString(text);
    _text.setPosition(position);
    _text.setCharacterSize(character_size);
    _text.setFillColor(color);
    _text.setOutlineColor(outline_color);
    _text.setOutlineThickness(outline_thickness);
}

void Button::updateState(sf::RenderWindow const &window, sf::Event event)
{
    if (_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        _state = (event.type == sf::Event::MouseButtonReleased) ? State::RELEASED
            : (event.type == sf::Event::MouseButtonPressed) ? State::CLICKED
            : State::HOVERED;
    else
        _state = State::IDLE;
}

Button::State Button::getState() const
{
    return _state;
}

void Button::update(sf::RenderWindow const &window, float const elapsed_time)
{
    _hovered.update(_text, elapsed_time, _state == State::HOVERED, _position);
    _clicked.update(_text, elapsed_time, _state == State::CLICKED || _state == State::RELEASED, _position);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_box, states);
    target.draw(_text, states);
}