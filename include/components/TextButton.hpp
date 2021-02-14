#ifndef TEXTBUTTON_HPP
    #define TEXTBUTTON_HPP

    #include <SFML/Window/Event.hpp>
    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Graphics/Text.hpp>

    class TextButton : public sf::Drawable
    {
    public:
        enum State {
            IDLE,
            HOVERED,
            CLICKED,
            RELEASED
        };
        enum AnimationType {
            ZOOM_IN,
            ZOOM_OUT,
            TOP_TO_BOTTOM_SLIDE,
            BOTTOM_TO_TOP_SLIDE,
            LEFT_TO_RIGHT_SLIDE,
            RIGHT_TO_LEFT_SLIDE
        };

    private:
        sf::Text _text;
        AnimationType _animation;
        float _animation_duration;
        float _animation_intensity;
        unsigned int _animation_iteration;
        unsigned int _animation_state;
        float _elapsed_time;
        State _state;
        sf::Vector2f _position;

    public:
        TextButton(
            sf::String const &text,
            sf::Font const &font,
            sf::Vector2f const &position = {0.0f, 0.0f},
            unsigned int const size = 30U,
            sf::Color const &color = sf::Color::White,
            sf::Color const &outline_color = sf::Color::Black,
            float const outline_thickness = 0.0f,
            AnimationType const animation = AnimationType::ZOOM_IN,
            float const animation_duration = 0.1f,
            float const animation_intensity = 1.2f,
            unsigned int const animation_iteraion = 100U
        );
        TextButton() = delete;
        ~TextButton() = default;

        void updateState(sf::RenderWindow const &window, sf::Event event);
        State getState() const;
        void update(sf::RenderWindow const &window, float const elapsed_time = 0.0f);
        void updateAnimation();

        sf::Vector2f const &getPosition() const;
        void setPosition(sf::Vector2f const &position);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
#endif