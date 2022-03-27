#include <SFML/Window/Event.hpp>
#include "components/Switch.hpp"

Switch::Switch(sf::Vector2f const &position, const float size, sf::Color const &unchecked_color, sf::Color const &checked_color, sf::Color const &background_color, const float border_thickness, bool checked)
: _checked{checked}, _clicked{false}, _position{position}, _size{size}, _unchecked_color{unchecked_color}, _checked_color{checked_color}, _background_color{background_color}, _border_thickness{border_thickness}, _animation{Animation::Type::LEFT_TO_RIGHT_SLIDE, 0.1f, size}, _background{}, _picker{}
{
	__init__();
}

Switch::Switch(Switch const &other)
: _checked{other._checked}, _clicked{other._clicked}, _position{other._position}, _size{other._size}, _unchecked_color{other._unchecked_color}, _checked_color{other._checked_color}, _background_color{other._background_color}, _border_thickness{other._border_thickness}, _animation{other._animation}, _background{other._background}, _picker{other._picker}
{
	__init__();
}

Switch &Switch::operator=(Switch const &other)
{
	this->_checked = other._checked;
	this->_clicked = other._clicked;
	this->_position = other._position;
	this->_size = other._size;
	this->_unchecked_color = other._unchecked_color;
	this->_checked_color = other._checked_color;
	this->_background_color = other._background_color;
	this->_border_thickness = other._border_thickness;
	this->_animation = other._animation;
	this->__init__();
	return *this;
}

void Switch::__init__()
{
	_background.setSize({2.0f * _size - (2.0f * _border_thickness), _size - (2.0f * _border_thickness)});
	_background.setPosition({_position.x + _border_thickness, _position.y + _border_thickness});
	_background.setCornersRadius(_size / 2.0f - _border_thickness);
	_background.setCornerPointCount(10);
	_background.setFillColor(_background_color);
	_background.setOutlineColor(_checked ? _checked_color : _unchecked_color);
	_background.setOutlineThickness(_border_thickness);

	_picker.setRadius(_size / 2.0f - (2 * _border_thickness));
	_picker.setOrigin({_picker.getRadius(), _picker.getRadius()});
	_picker.setFillColor(_checked ? _checked_color : _unchecked_color);
	_picker.setPosition({_position.x + (2 * _border_thickness) + _picker.getRadius(), _position.y + (2 * _border_thickness) + _picker.getRadius()});
}

bool Switch::checked() const
{
	return _checked;
}

void Switch::check(bool value)
{
	_checked = value;
}

bool Switch::picker_contains(sf::Vector2f const &point) const
{
	float a = (point.x - _picker.getPosition().x);
	float b = (point.y - _picker.getPosition().y);

	return (((a * a) + (b * b)) < (_picker.getRadius() * _picker.getRadius()));
}

sf::Color Switch::_compute_color() const
{
	float percent = static_cast<float>(_animation.state) / static_cast<float>(_animation.iteration);

	return sf::Color(
		_unchecked_color.r + static_cast<sf::Uint8>(percent * (_checked_color.r - _unchecked_color.r)),
		_unchecked_color.g + static_cast<sf::Uint8>(percent * (_checked_color.g - _unchecked_color.g)),
		_unchecked_color.b + static_cast<sf::Uint8>(percent * (_checked_color.b - _unchecked_color.b)),
		_unchecked_color.a + static_cast<sf::Uint8>(percent * (_checked_color.a - _unchecked_color.a))
	);
}

void Switch::update(sf::RenderWindow const &window, const float elapsed_time)
{
	if (_background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_clicked = true;
		} else if (_clicked) {
			_checked = !_checked;
			_clicked = false;
		}
	} else {
		_clicked = false;
	}
	_animation.update(_picker, elapsed_time, _checked, {_position.x + (2 * _border_thickness) + _picker.getRadius(), _position.y + (2 * _border_thickness) + _picker.getRadius()});
	sf::Color color = _compute_color();
	_background.setOutlineColor(color);
	_picker.setFillColor(color);
}

void Switch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_background, states);
	target.draw(_picker, states);
}