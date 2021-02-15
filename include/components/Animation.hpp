#pragma once

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

    Animation(Type const type = Type::NONE, float const duration = 0.1f, float const intensity = 1.2f, unsigned int const iteration = 100U)
        : type{type}, duration{duration}, intensity{intensity}, iteration{iteration}, state{0U}, time{0.0f} {}
    Animation(Animation const &other)
        : type{other.type}, duration{other.duration}, intensity{other.intensity}, iteration{other.iteration}, state{0U}, time{0.0f} {}
    ~Animation() = default;
};