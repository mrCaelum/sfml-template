#pragma once

#include <vector>
#include "TextButton.hpp"

class TextMenu : public sf::Drawable
{
private:
    std::vector<TextButton> _buttons;
    sf::Font _font;
    unsigned int _character_size;
    sf::Color _text_color;
    sf::Color _text_outline_color;
    float _outline_thickness;
    TextButton::Origin _origin;
    Animation _hovered;
    Animation _clicked;

public:
    TextMenu(
        sf::Font const &font,
        unsigned int const character_size = 30U,
        sf::Color const &text_color = sf::Color::White,
        sf::Color const &text_outline_color = sf::Color::Black,
        float const outline_thickness = 0.0f,
        TextButton::Origin const origin = TextButton::Origin::CENTERED,
        Animation const &hovered = Animation{},
        Animation const &clicked = Animation{}
    );
    TextMenu() = delete;
    ~TextMenu() = default;

    void updateStates(sf::RenderWindow const &window, sf::Event event);
    void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

    void addButton(sf::String const &text, sf::Vector2f const &position);
    TextButton *getButton(sf::String const &text);
    std::vector<TextButton::State> const &getStates() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};