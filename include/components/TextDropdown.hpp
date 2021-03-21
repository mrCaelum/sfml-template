#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

class TextDropdownElement : public sf::Drawable
{
private:
    sf::Vector2f _size;
    sf::Text _text;
    sf::RectangleShape _box;

public:
    TextDropdownElement(
        sf::Font const &font,
        sf::String const &text,
        sf::Vector2f const &size,
        unsigned int character_size
    );
    ~TextDropdownElement() = default;

    sf::String getValue() const;
    void setPosition(sf::Vector2f const &position);

    bool update(sf::Vector2f const &mouse_position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class TextDropdown : public sf::Drawable
{
public:
    enum State {
        IDLE,
        CLICKED,
        RELEASED
    };

private:
    sf::Font _font;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Vector2f _dropdown_size;
    unsigned int _character_size;
    sf::Color _primary_color;
    sf::Color _background_color;
    sf::RectangleShape _box;
    sf::CircleShape _arrow;
    sf::Text _selectedText;
    sf::RenderTexture _texture_frame;
    sf::Sprite _frame;
    std::vector<TextDropdownElement> _elements;
    Animation _arrow_clicked;
    State _state;
    bool _unwrapped;
    bool _changed;

public:
    TextDropdown(
        sf::Font const &font,
        sf::String const &placeholder,
        sf::Vector2f const &position,
        sf::Vector2f const &size = {200.0f, 40.0f},
        sf::Vector2f const &dropdown_size = {200.0f, 200.0f},
        unsigned int character_size = 20U,
        sf::Color const &primary_color = sf::Color{52, 152, 219},
        sf::Color const &background_color = sf::Color{80, 80, 80},
        Animation const &arrow_clicked = Animation{Animation::Type::NEGATIVE_ROTATION, 0.1f, 60.0f}
    );
    TextDropdown() = delete;
    ~TextDropdown() = default;

    void addElement(sf::String const &text);

    bool changed();
    sf::String getValue() const;
    void setValue(sf::String const &text);

    void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};