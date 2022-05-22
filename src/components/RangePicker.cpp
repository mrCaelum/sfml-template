#include <SFML/Window/Event.hpp>
#include "Core.hpp"
#include "components/RangePicker.hpp"

RangePicker::RangePicker(unsigned int range, sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color bar_color)
: _range{range}, _position{position}, _size{size}, _color{color}, _value{3U}, _point{}, _line{}, _selected{false}
{
	static const float bar_height_factor{6.0f};

	_point.setRadius(_size.y / 2.0f);
	_point.setOrigin({_point.getRadius(), _point.getRadius()});
	_point.setFillColor(color);
	_point.setPosition({static_cast<float>(_value) * _size.x / static_cast<float>(_range) + _position.x, _position.y + (_size.y / 2.0f)});

	_line.setSize({_size.x, _size.y / bar_height_factor});
	_line.setOrigin({_line.getSize().x / 2, _line.getSize().y / 2});
	_line.setFillColor(bar_color);
	_line.setPosition({_position.x + (_size.x / 2.0f), _position.y + (_size.y / 2.0f)});
}

RangePicker::RangePicker(RangePicker const &other)
: _range{other._range}, _position{other._position}, _size{other._size}, _color{other._color}, _value{other._value}, _point{other._point}, _selected{other._selected}
{}

RangePicker &RangePicker::operator=(RangePicker const &other)
{
	this->_range = other._range;
	this->_position = other._position;
	this->_size = other._size;
	this->_color = other._color;
	this->_value = other._value;
	this->_point = other._point;
	this->_selected = other._selected;
	return *this;
}

unsigned int RangePicker::getValue() const
{
	return _value;
}

sf::Vector2f const &RangePicker::getPosition() const
{
	return _position;
}

void RangePicker::setPosition(sf::Vector2f const &position)
{
	_position = position;
}

bool RangePicker::contains(sf::Vector2f const &point) const
{
	float a = (point.x - _point.getPosition().x);
	float b = (point.y - _point.getPosition().y);

	return (((a * a) + (b * b)) < (_point.getRadius() * _point.getRadius()));
}

void RangePicker::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mouse_pos_i{sf::Mouse::getPosition(Core::WINDOW)};
		sf::Vector2f mouse_position{static_cast<float>(mouse_pos_i.x), static_cast<float>(mouse_pos_i.y)};
		if (contains(mouse_position)) {
			_selected = true;
			_point.setFillColor(sf::Color(_color.r * 2, _color.g * 2, _color.b * 2));
		}
		if (_selected || _line.getGlobalBounds().contains(mouse_position)) {
			if (mouse_position.x < _position.x) {
				_value = 0U;
			} else if (mouse_position.x > _position.x + _size.x) {
				_value = _range;
			} else {
				_value = static_cast<unsigned int>((mouse_position.x - _position.x + (_size.x / static_cast<float>(_range) / 2.0f)) * static_cast<float>(_range) / _size.x);
			}
		}
	} else if (_selected) {
		_selected = false;
		_point.setFillColor(_color);
	}
	_point.setPosition({static_cast<float>(_value) * _size.x / static_cast<float>(_range) + _position.x, _position.y + (_size.y / 2.0f)});
}

void RangePicker::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_line, states);
	target.draw(_point, states);
}