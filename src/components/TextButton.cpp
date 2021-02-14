#include <SFML/Window/Mouse.hpp>
#include "TextButton.hpp"

TextButton::TextButton(sf::String const &text, sf::Font const &font, sf::Vector2f const &position, unsigned int const size, sf::Color const &color, sf::Color const &outline_color, float const outline_thickness, AnimationType const animation, float const animation_duration, float const animation_intensity, unsigned int const animation_iteration)
: _text{}, _position{position}, _animation{animation}, _animation_duration{animation_duration}, _animation_intensity{animation_intensity}, _animation_iteration{animation_iteration}, _animation_state{0}, _elapsed_time{0.0f}, _state{State::IDLE}
{
    _text.setFont(font);
    _text.setString(text);
    _text.setPosition(position);
    _text.setCharacterSize(size);
    _text.setFillColor(color);
    _text.setOutlineColor(outline_color);
    _text.setOutlineThickness(outline_thickness);
    switch (_animation) {
    case AnimationType::TOP_TO_BOTTOM_SLIDE:
        _text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height);
        break;
    case AnimationType::BOTTOM_TO_TOP_SLIDE:
        _text.setOrigin(_text.getLocalBounds().width / 2, 0.0f);
        break;
    case AnimationType::LEFT_TO_RIGHT_SLIDE:
        _text.setOrigin(0.0f, _text.getLocalBounds().height / 2);
        break;
    case AnimationType::RIGHT_TO_LEFT_SLIDE:
        _text.setOrigin(_text.getLocalBounds().width, _text.getLocalBounds().height / 2);
        break;
    default:
        _text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
        break;
    }
}

void TextButton::updateState(sf::RenderWindow const &window, sf::Event event)
{
    if (_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
        _state = (event.type == sf::Event::MouseButtonReleased) ? State::RELEASED
            : (event.type == sf::Event::MouseButtonPressed) ? State::CLICKED
            : State::HOVERED;
    else
        _state = State::IDLE;
}

TextButton::State TextButton::getState() const
{
    return _state;
}

void TextButton::update(sf::RenderWindow const &window, float const elapsed_time)
{
    _elapsed_time += elapsed_time;
    while (_elapsed_time >= (_animation_duration / static_cast<float>(_animation_iteration))) {
        _elapsed_time -= (_animation_duration / static_cast<float>(_animation_iteration));
        updateAnimation();
    }
}

void TextButton::updateAnimation()
{
    if (_state == State::IDLE) {
        if (_animation_state > 0)
            --_animation_state;
    } else {
        if (_animation_state <= _animation_iteration)
            ++_animation_state;
    }
    switch (_animation) {
        case AnimationType::ZOOM_IN:
            _text.setScale(sf::Vector2f{1.0f, 1.0f} * ((_animation_state * (_animation_intensity - 1.0f) / _animation_iteration) + 1.0f));
            break;
        case AnimationType::ZOOM_OUT:
            _text.setScale(sf::Vector2f{1.0f, 1.0f} / ((_animation_state * (_animation_intensity - 1.0f) / _animation_iteration) + 1.0f));
            break;
        case AnimationType::TOP_TO_BOTTOM_SLIDE:
            _text.setPosition(sf::Vector2f{_position.x, _position.y * ((_animation_state * (((_animation_intensity - 1.0f) / 10 + 1.0f) - 1.0f) / _animation_iteration) + 1.0f)});
            break;
        case AnimationType::BOTTOM_TO_TOP_SLIDE:
            _text.setPosition(sf::Vector2f{_position.x, _position.y / ((_animation_state * (((_animation_intensity - 1.0f) / 10 + 1.0f) - 1.0f) / _animation_iteration) + 1.0f)});
            break;
        case AnimationType::LEFT_TO_RIGHT_SLIDE:
            _text.setPosition(sf::Vector2f{_position.x * ((_animation_state * (((_animation_intensity - 1.0f) / 10 + 1.0f) - 1.0f) / _animation_iteration) + 1.0f), _position.y});
            break;
        case AnimationType::RIGHT_TO_LEFT_SLIDE:
            _text.setPosition(sf::Vector2f{_position.x / ((_animation_state * (((_animation_intensity - 1.0f) / 10 + 1.0f) - 1.0f) / _animation_iteration) + 1.0f), _position.y});
            break;
        }
}

sf::String const &TextButton::getString() const
{
    return _text.getString();
}

sf::Vector2f const &TextButton::getPosition() const
{
    return _text.getPosition();
}

void TextButton::setPosition(sf::Vector2f const &position)
{
    _position = position;
    _text.setPosition(position);
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_text, states);
}