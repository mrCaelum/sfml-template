#include <SFML/Window/Event.hpp>
#include "Switch.hpp"

Switch::Switch(sf::Vector2f const &position, const float size, sf::Color const &color, sf::Color const &background_color, const float border_thickness, bool checked)
: _checked{checked}, _position{position}, _size{size}, _border_thickness{border_thickness}, _animation{Animation::Type::LEFT_TO_RIGHT_SLIDE, 0.1f, size / 7.0f}, _mouse_clicked{false}, _center_border{}, _left_background{}, _right_background{}, _center_background{}, _picker{}
{
    _center_border.setSize({_size, _size});
    _center_border.setFillColor(color);
    _center_border.setPosition({_position.x + _size / 2.0f, _position.y});

    _left_background.setRadius(_size / 2.0f - _border_thickness);
    _left_background.setFillColor(background_color);
    _left_background.setOutlineColor(color);
    _left_background.setOutlineThickness(_border_thickness);
    _left_background.setPosition({_position.x + _border_thickness, _position.y + _border_thickness});

    _right_background.setRadius(_size / 2.0f - _border_thickness);
    _right_background.setFillColor(background_color);
    _right_background.setOutlineColor(color);
    _right_background.setOutlineThickness(_border_thickness);
    _right_background.setPosition({_position.x + _size + _border_thickness, _position.y + _border_thickness});

    _center_background.setSize({_size, _size - (2 * _border_thickness)});
    _center_background.setFillColor(background_color);
    _center_background.setPosition({_position.x + _size / 2.0f, _position.y + _border_thickness});

    _picker.setRadius(_size / 2.0f - (2 * _border_thickness));
    _picker.setFillColor(color);
    _picker.setPosition({_position.x + (2 * _border_thickness), _position.y + (2 * _border_thickness)});
}

bool Switch::checked() const
{
    return _checked;
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

void Switch::update(sf::RenderWindow const &window, const float elapsed_time)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _mouse_clicked = true;
    } else if (_mouse_clicked) {
        sf::Vector2i mouse_pos_i{sf::Mouse::getPosition(window)};
        sf::Vector2f mouse_position{static_cast<float>(mouse_pos_i.x), static_cast<float>(mouse_pos_i.y)};

        if (contains(mouse_position)) {
            _checked = !_checked;
        }
        _mouse_clicked = false;
    }
    _animation.update(_picker, elapsed_time, _checked, {_position.x + (2 * _border_thickness), _position.y + (2 * _border_thickness)});
}

void Switch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_center_border, states);
    target.draw(_left_background, states);
    target.draw(_right_background, states);
    target.draw(_center_background, states);
    target.draw(_picker, states);
}