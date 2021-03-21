#include <SFML/Window/Event.hpp>
#include "Switch.hpp"

Switch::Switch(sf::Vector2f const &position, const float size, sf::Color const &unchecked_color, sf::Color const &checked_color, sf::Color const &background_color, const float border_thickness, bool checked)
: _checked{checked}, _position{position}, _size{size}, _unchecked_color{unchecked_color}, _checked_color{checked_color}, _border_thickness{border_thickness}, _animation{Animation::Type::LEFT_TO_RIGHT_SLIDE, 0.1f, size}, _mouse_state{0U}, _center_border{}, _left_background{}, _right_background{}, _center_background{}, _picker{}
{
    _center_border.setSize({_size, _size});
    _center_border.setOrigin(_center_border.getSize() / 2.0f);
    _center_border.setFillColor(_checked ? _checked_color : _unchecked_color);
    _center_border.setPosition({_position.x + _size / 2.0f + _center_border.getSize().x / 2.0f, _position.y + _center_border.getSize().y / 2.0f});

    _left_background.setRadius(_size / 2.0f - _border_thickness);
    _left_background.setOrigin({_left_background.getRadius(), _left_background.getRadius()});
    _left_background.setFillColor(background_color);
    _left_background.setOutlineColor(_checked ? _checked_color : _unchecked_color);
    _left_background.setOutlineThickness(_border_thickness);
    _left_background.setPosition({_position.x + _border_thickness + _left_background.getRadius(), _position.y + _border_thickness + _left_background.getRadius()});

    _right_background.setRadius(_size / 2.0f - _border_thickness);
    _right_background.setOrigin({_right_background.getRadius(), _right_background.getRadius()});
    _right_background.setFillColor(background_color);
    _right_background.setOutlineColor(_checked ? _checked_color : _unchecked_color);
    _right_background.setOutlineThickness(_border_thickness);
    _right_background.setPosition({_position.x + _size + _border_thickness + _right_background.getRadius(), _position.y + _border_thickness + _right_background.getRadius()});

    _center_background.setSize({_size, _size - (2 * _border_thickness)});
    _center_background.setOrigin(_center_background.getSize() / 2.0f);
    _center_background.setFillColor(background_color);
    _center_background.setPosition({_position.x + _size / 2.0f + _center_background.getSize().x / 2.0f, _position.y + _border_thickness + _center_background.getSize().y / 2.0f});

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

bool Switch::contains(sf::Vector2f const &point) const
{
    float a = (point.x - _left_background.getPosition().x);
    float b = (point.y - _left_background.getPosition().y);

    if (((a * a) + (b * b)) < (_left_background.getRadius() * _left_background.getRadius()))
        return true;
    
    a = (point.x - _right_background.getPosition().x);
    b = (point.y - _right_background.getPosition().y);

    if (((a * a) + (b * b)) < (_right_background.getRadius() * _right_background.getRadius()))
        return true;
    
    return _center_border.getGlobalBounds().contains(point);
}

sf::Color Switch::_compute_color() const
{
    float percent = static_cast<float>(_animation.state) / static_cast<float>(_animation.iteration);

    return sf::Color(
        _unchecked_color.r + percent * (_checked_color.r - _unchecked_color.r),
        _unchecked_color.g + percent * (_checked_color.g - _unchecked_color.g),
        _unchecked_color.b + percent * (_checked_color.b - _unchecked_color.b),
        _unchecked_color.a + percent * (_checked_color.a - _unchecked_color.a)
    );
}

void Switch::update(sf::RenderWindow const &window, const float elapsed_time)
{
    sf::Vector2i mouse_pos_i{sf::Mouse::getPosition(window)};
    sf::Vector2f mouse_position{static_cast<float>(mouse_pos_i.x), static_cast<float>(mouse_pos_i.y)};

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_mouse_state == MouseState::IDLE && picker_contains(mouse_position)) {
            _mouse_state = MouseState::CLICKED_ON;
        }
        if (_mouse_state == MouseState::CLICKED_ON) {
            if (mouse_position.x < (_position.x + (2 * _border_thickness) + _picker.getRadius())) {
                _animation.state = 0U;
                _checked = false;
            } else if (mouse_position.x > (_position.x + (2 * _border_thickness) + _picker.getRadius() + _size)) {
                _animation.state = _animation.iteration;
                _checked = true;
            } else {
                _animation.state = (mouse_position.x - (_position.x + (2 * _border_thickness) + _picker.getRadius())) * _animation.iteration / _size;
                _checked = _animation.state < _animation.iteration / 2;
            }
        } else {
            _mouse_state = MouseState::CLICKED;
        }
    } else if (_mouse_state == MouseState::CLICKED || _mouse_state == MouseState::CLICKED_ON) {
        if (contains(mouse_position)) {
            _checked = !_checked;
        }
        _mouse_state = MouseState::IDLE;
    }
    _animation.update(_picker, elapsed_time, _checked, {_position.x + (2 * _border_thickness) + _picker.getRadius(), _position.y + (2 * _border_thickness) + _picker.getRadius()});
    sf::Color color = _compute_color();
    _center_border.setFillColor(color);
    _left_background.setOutlineColor(color);
    _right_background.setOutlineColor(color);
    _picker.setFillColor(color);
}

void Switch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_center_border, states);
    target.draw(_left_background, states);
    target.draw(_right_background, states);
    target.draw(_center_background, states);
    target.draw(_picker, states);
}