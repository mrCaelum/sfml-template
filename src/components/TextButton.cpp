#include <SFML/Window/Mouse.hpp>
#include "Core.hpp"
#include "components/TextButton.hpp"

TextButton::TextButton(sf::Font const &font, sf::String const &text, sf::Vector2f const &position, unsigned int const size, sf::Color const &color, sf::Color const &outline_color, float const outline_thickness, Origin const origin, Animation const &hovered, Animation const &clicked)
: _text{}, _position{position}, _hovered{hovered}, _clicked{clicked}, _elapsed_time{0.0f}, _state{State::IDLE}
{
	_text.setFont(font);
	_text.setString(text);
	_text.setPosition(position);
	_text.setCharacterSize(size);
	_text.setFillColor(color);
	_text.setOutlineColor(outline_color);
	_text.setOutlineThickness(outline_thickness);
	setOrigin(origin);
}

void TextButton::updateState(sf::Event event)
{
	if (_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(Core::WINDOW))))
		_state = (event.type == sf::Event::MouseButtonReleased) ? State::RELEASED
			: (event.type == sf::Event::MouseButtonPressed) ? State::CLICKED
			: State::HOVERED;
	else
		_state = State::IDLE;
}

TextButton::State TextButton::getState() const
{
	return _state;
}

void TextButton::update(float const elapsed_time)
{
	_hovered.update(_text, elapsed_time, _state == State::HOVERED, _position);
	_clicked.update(_text, elapsed_time, _state == State::CLICKED || _state == State::RELEASED, _position);
}

sf::String const &TextButton::getString() const
{
	return _text.getString();
}

sf::Vector2f const &TextButton::getPosition() const
{
	return _text.getPosition();
}

void TextButton::setPosition(sf::Vector2f const &position)
{
	_position = position;
	_text.setPosition(position);
}

void TextButton::setOrigin(Origin const origin)
{
	switch (origin) {
	case Origin::CENTERED:
		_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
		break;
	case Origin::LEFT:
		_text.setOrigin(0.0f, _text.getLocalBounds().height / 2);
		break;
	case Origin::TOP:
		_text.setOrigin(_text.getLocalBounds().width / 2, 0.0f);
		break;
	case Origin::RIGHT:
		_text.setOrigin(_text.getLocalBounds().width, _text.getLocalBounds().height / 2);
		break;
	case Origin::BOTTOM:
		_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height);
		break;
	case Origin::TOP_LEFT:
		_text.setOrigin(0.0f, 0.0f);
		break;
	case Origin::TOP_RIGHT:
		_text.setOrigin(_text.getLocalBounds().width, 0.0f);
		break;
	case Origin::BOTTOM_LEFT:
		_text.setOrigin(0.0f, _text.getLocalBounds().height);
		break;
	case Origin::BOTTOM_RIGHT:
		_text.setOrigin(_text.getLocalBounds().width, _text.getLocalBounds().height);
		break;
	}
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_text, states);
}