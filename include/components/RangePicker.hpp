#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class RangePicker : public sf::Drawable
{
private:
    unsigned int _range;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Color _color;
    unsigned int _value;
    sf::CircleShape _point;
    sf::RectangleShape _line;
    sf::CircleShape _left_bound;
    sf::CircleShape _right_bound;
    sf::RectangleShape _borders;
    bool _selected;

public:
    RangePicker(
        unsigned int range,
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color = sf::Color(52, 152, 219),
        sf::Color bar_color = sf::Color(236, 240, 241)
    );
    RangePicker() = delete;
    ~RangePicker() = default;

    void setValue(unsigned int value);
    unsigned int getValue() const;

    sf::Vector2f const &getPosition() const;
    void setPosition(sf::Vector2f const &position);

    bool contains(sf::Vector2f const &point) const;

    void update(sf::RenderWindow const &window);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};