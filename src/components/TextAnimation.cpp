#include "TextAnimation.hpp"

TextAnimation::TextAnimation(Type const type, float const duration, float const intensity, unsigned int const iteration)
: Animation{type, duration, intensity, iteration} {}

void TextAnimation::update(sf::Text &text, float const elapsed_time, bool anim, sf::Vector2f const &position)
{
    this->time += elapsed_time;
    while (this->time >= (this->duration / static_cast<float>(this->iteration))) {
        this->time -= (this->duration / static_cast<float>(this->iteration));

        if (!anim) {
            if (this->state > 0)
                --this->state;
        } else {
            if (this->state <= this->iteration)
                ++this->state;
        }
        switch (this->type) {
        case Animation::Type::ZOOM_IN:
            text.setScale(sf::Vector2f{1.0f, 1.0f} * ((this->state * (this->intensity - 1.0f) / this->iteration) + 1.0f));
            break;
        case Animation::Type::ZOOM_OUT:
            text.setScale(sf::Vector2f{1.0f, 1.0f} / ((this->state * (this->intensity - 1.0f) / this->iteration) + 1.0f));
            break;
        case Animation::Type::TOP_TO_BOTTOM_SLIDE:
            text.setPosition(sf::Vector2f{position.x, position.y * ((this->state * (((this->intensity - 1.0f) / 10 + 1.0f) - 1.0f) / this->iteration) + 1.0f)});
            break;
        case Animation::Type::BOTTOM_TO_TOP_SLIDE:
            text.setPosition(sf::Vector2f{position.x, position.y / ((this->state * (((this->intensity - 1.0f) / 10 + 1.0f) - 1.0f) / this->iteration) + 1.0f)});
            break;
        case Animation::Type::LEFT_TO_RIGHT_SLIDE:
            text.setPosition(sf::Vector2f{position.x * ((this->state * (((this->intensity - 1.0f) / 10 + 1.0f) - 1.0f) / this->iteration) + 1.0f), position.y});
            break;
        case Animation::Type::RIGHT_TO_LEFT_SLIDE:
            text.setPosition(sf::Vector2f{position.x / ((this->state * (((this->intensity - 1.0f) / 10 + 1.0f) - 1.0f) / this->iteration) + 1.0f), position.y});
            break;
        }
    }
}