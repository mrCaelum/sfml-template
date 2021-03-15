#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class TextDropdownElement : public sf::Drawable
{
private:
    sf::Text _text;

public:
    TextDropdownElement(sf::String const &text);
    ~TextDropdownElement() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class TextDropdown : public sf::Drawable
{
private:
    sf::Vector2f _position;
    sf::RectangleShape _box;
    sf::CircleShape _arrow;
    sf::Text _selectedText;
    sf::RenderTexture _frame;

public:
    TextDropdown(
        sf::Font const &font,
        sf::String const &placeholder,
        sf::Vector2f const &position,
        sf::Vector2f const &size = {200.0f, 40.0f},
        unsigned int character_size = 20U,
        sf::Color primary_color = sf::Color(52, 152, 219),
        sf::Color background_color = sf::Color(80, 80, 80)
    );
    TextDropdown() = delete;
    ~TextDropdown() = default;

    sf::Vector2f const &getPosition() const;
    void setPosition(sf::Vector2f const &position);

    void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};