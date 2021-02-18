#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Animation.hpp"

class Switch : public sf::Drawable
{
private:
    bool _checked;
    sf::Vector2f _position;
    float _size;
    float _border_thickness;
    Animation _animation;
    bool _mouse_clicked;

    sf::RectangleShape _center_border;
    sf::CircleShape _left_background;
    sf::CircleShape _right_background;
    sf::RectangleShape _center_background;
    sf::CircleShape _picker;

public:
    Switch(
        sf::Vector2f const &position,
        const float size,
        sf::Color const &color = sf::Color(52, 152, 219),
        sf::Color const &background_color = sf::Color(236, 240, 241),
        const float border_thickness = 2.0f,
        bool checked = false
    );
    ~Switch() = default;

    bool checked() const;

    bool contains(sf::Vector2f const &point) const;

    void update(sf::RenderWindow const &window, const float elapsed_time = 0.0f);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};