#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Animation.hpp"

class TextAnimation : public Animation
{
public:
    TextAnimation(Type const type = Type::NONE, float const duration = 0.1f, float const intensity = 1.2f, unsigned int const iteration = 100U);
    ~TextAnimation() = default;

    void update(sf::Text &text, float const elapsed_time, bool anim = false, sf::Vector2f const &position = {0.0f, 0.0f});
};