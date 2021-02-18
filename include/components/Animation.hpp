#pragma once

#include <SFML/Graphics/Transformable.hpp>

struct Animation
{
    enum Type {
        NONE,
        ZOOM_IN,
        ZOOM_OUT,
        TOP_TO_BOTTOM_SLIDE,
        BOTTOM_TO_TOP_SLIDE,
        LEFT_TO_RIGHT_SLIDE,
        RIGHT_TO_LEFT_SLIDE
    };

    Type const type;
    float const duration;
    float const intensity;
    unsigned int const iteration;
    unsigned int state;
    float time;

    Animation(Type const type = Type::NONE, float const duration = 0.1f, float const intensity = 1.2f, unsigned int const iteration = 100U);
    Animation(Animation const &other);
    ~Animation() = default;

    void update(sf::Transformable &transform, float const elapsed_time, bool anim = false, sf::Vector2f const &position = {0.0f, 0.0f});
};