#include "components/Button.hpp"

#define DARKER(x, y) (sf::Color{x.r / y, x.g / y, x.b / y, x.a})

Button::Button(sf::Font const &font, sf::String const &text, sf::Vector2f const &position, sf::Vector2f const &size, unsigned int const character_size, sf::Color const &text_color, sf::Color const &background_color, sf::Color const &border_color, float const border_thickness, Animation const &hovered, Animation const &clicked)
: disabled{false}, _box{}, _text{}, _position{position}, _text_color{text_color}, _background_color{background_color}, _border_color{border_color}, _hovered{hovered}, _clicked{clicked}, _elapsed_time{0.0f}, _state{State::IDLE}
{
	_box.setPosition(position);
	_box.setSize(size);
	_box.setFillColor(_background_color);
	_box.setOutlineColor(_border_color);
	_box.setOutlineThickness(border_thickness);

	_text.setFont(font);
	_text.setString(text);
	_text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
	_text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
	_text.setCharacterSize(character_size);
	_text.setFillColor(_text_color);
}

Button::Button(Button const &other)
: disabled{other.disabled}, _box{other._box}, _text{other._text}, _position{other._position}, _text_color{other._text_color}, _background_color{other._background_color}, _border_color{other._border_color}, _hovered{other._hovered}, _clicked{other._clicked}, _elapsed_time{other._elapsed_time}, _state{other._state}
{}

Button &Button::operator=(Button const &other)
{
	this->disabled = other.disabled;
	this->_box = other._box;
	this->_text = other._text;
	this->_position = other._position;
	this->_text_color = other._text_color;
	this->_background_color = other._background_color;
	this->_border_color = other._border_color;
	this->_hovered = other._hovered;
	this->_clicked = other._clicked;
	this->_elapsed_time = other._elapsed_time;
	this->_state = other._state;
	return *this;
}

bool Button::hovered() const
{
	return _state == State::HOVERED;
}

bool Button::clicked() const
{
	return _state == State::CLICKED;
}

bool Button::released() const
{
	return _state == State::RELEASED;
}

void Button::update(sf::RenderWindow const &window, float const elapsed_time)
{
	_box.setFillColor(disabled ? DARKER(_background_color, 2u) : _background_color);
	_box.setOutlineColor(disabled ? DARKER(_border_color, 2u) : _border_color);
	_text.setFillColor(disabled ? DARKER(_text_color, 2u) : _text_color);
	if (_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_state = State::CLICKED;
		} else if (_state == State::CLICKED) {
			_state = State::RELEASED;
		} else {
			_state = State::HOVERED;
		}
	} else {
		_state = State::IDLE;
	}
	_hovered.update(_box, elapsed_time, _state == State::HOVERED, _position);
	_hovered.update(_text, 0.0f, _state == State::HOVERED, _position);
	_clicked.update(_box, elapsed_time, _state == State::CLICKED || _state == State::RELEASED, _position);
	_clicked.update(_text, 0.0f, _state == State::CLICKED || _state == State::RELEASED, _position);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_box, states);
	target.draw(_text, states);
}