#ifndef TEXTMENU_HPP
    #define TEXTMENU_HPP

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
        TextButton::AnimationType _animation;
        float _animation_duration;
        float _animation_intensity;
        unsigned int _animation_iteration;

    public:
        TextMenu(
            sf::Font const &font,
            unsigned int const character_size = 30U,
            sf::Color const &text_color = sf::Color::White,
            sf::Color const &text_outline_color = sf::Color::Black,
            float const outline_thickness = 0.0f,
            TextButton::AnimationType const animation = TextButton::AnimationType::ZOOM_IN,
            float const animation_duration = 0.1f,
            float const animation_intensity = 1.2f,
            unsigned int const animation_iteration = 100U
        );
        TextMenu() = delete;
        ~TextMenu() = default;

        void updateStates(sf::RenderWindow const &window, sf::Event event);
        void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);

        void addButton(sf::String const &text, sf::Vector2f const &position);
        TextButton *getButton(sf::String const &text);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
#endif