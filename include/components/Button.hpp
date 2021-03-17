#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

class Button : public sf::Drawable
{
public:
    enum State {
        IDLE,
        HOVERED,
        CLICKED,
        RELEASED
    };

private:
    sf::RectangleShape _box;
    sf::Text _text;
    sf::Vector2f _position;
    Animation _hovered;
    Animation _clicked;
    float _elapsed_time;
    State _state;

public:
    Button(
        sf::String const &text,
        sf::Font const &font,
        sf::Vector2f const &position = {0.0f, 0.0f},
        sf::Vector2f const &size = {200.0f, 50.0f},
        unsigned int const character_size = 30U,
        sf::Color const &color = sf::Color::White,
        sf::Color const &outline_color = sf::Color::Black,
        float const outline_thickness = 0.0f,
        Animation const &hovered = Animation{},
        Animation const &clicked = Animation{}
    );
    Button() = delete;
    ~Button() = default;

    void updateState(sf::RenderWindow const &window, sf::Event event);
    State getState() const;
    void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};