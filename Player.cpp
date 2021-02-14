#include <cmath>
#include "Player.hpp"

Player::Player(sf::RenderWindow const &window, sf::Vector2f const &position)
: _position{position}, _velocity{0.0f, 0.0f}, _texture{}, _sprite{}, _hitbox{}
{
    _texture.loadFromFile("assets/kaben.png");
    _sprite.setTexture(_texture);
    _sprite.setPosition(position.x * window.getSize().x / 100.0f, position.y * window.getSize().y / 100.0f);
    _sprite.setScale({0.15f, 0.15f});
    _sprite.setOrigin({_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2});
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(5);
    _hitbox.setRadius(_texture.getSize().x / 2.0f);
    _hitbox.setScale({0.15f, 0.15f});
    _hitbox.setOrigin({_hitbox.getLocalBounds().width / 2, _hitbox.getLocalBounds().height / 2});
}

void Player::stop()
{
    _velocity = {0.0f, 0.0f};
}

void Player::addVelocity(sf::Vector2f const &vector)
{
    static const float maxVelocity(0.25f);

    _velocity += vector;
    if (_velocity.x > maxVelocity || _velocity.x < -maxVelocity || _velocity.y > maxVelocity || _velocity.y < -maxVelocity)
        _velocity /= 2.0f;
}

void Player::move(sf::Vector2f const &to)
{
    _position += to;
}

void Player::setPosition(sf::Vector2f const &point)
{
    _position = point;
}

sf::Vector2f const &Player::getPosition() const
{
    return _position;
}

bool Player::contains(sf::Vector2f const &point) const
{
    sf::Vector2f center = _hitbox.getPosition();
    float a = (point.x - center.x);
    float b = (point.y - center.y);
    a *= a;
    b *= b;
    float r = _hitbox.getRadius() * _hitbox.getRadius();

    return (( a + b ) < r);
}

sf::Vector2f const &Player::getCollisionTestPoint(sf::RenderWindow const &window, sf::FloatRect const &object) const
{
    sf::Vector2f c(_position);
    sf::Vector2f test(c);

    if (c.x < object.left)
        test.x = object.left;
    else if (c.x > object.left + object.width)
        test.x = object.left + object.width;
    if (c.y < object.top)
        test.y = object.top;
    else if (object.top + object.height)
        test.y = object.top + object.height;
    return test;
}

bool Player::intersect(sf::RenderWindow const &window, sf::FloatRect const &object) const
{
    sf::Vector2f distance(_position - getCollisionTestPoint(window, object));

    return std::sqrt((distance.x * distance.x) + (distance.y * distance.y) <= _hitbox.getRadius());
}

bool Player::intersect(sf::RectangleShape const &object) const
{
    return intersect(object.getGlobalBounds());
}

sf::Vector2f Player::getDistanceFrom(sf::FloatRect const &object) const
{
    return getCollisionTestPoint(object) - _hitbox.getPosition();
}

sf::Vector2f Player::getDistanceTo(sf::FloatRect const &object) const
{
    sf::Vector2f o = _hitbox.getPosition();
    float r = _hitbox.getRadius();
    sf::Vector2f op(getDistanceFrom(object));
    float h = std::sqrt((op.x * op.x) + (op.y * op.y));
    sf::Vector2f og(op.x / (h / r), op.y / (h / r));

    return og - op;
}

sf::Vector2f Player::getDistanceFrom(sf::RectangleShape const &object) const
{
    return getDistanceFrom(object.getLocalBounds());
}

sf::Vector2f Player::getDistanceTo(sf::RectangleShape const &object) const
{
    return getDistanceTo(object.getLocalBounds());
}

void Player::update(sf::RenderWindow const &window, bool const timed)
{
    if (timed) {
        _position += _velocity;
        _velocity /= 1.2f;
    }
    _sprite.setPosition(_position.x * window.getSize().x / 100.0f, _position.y * window.getSize().y / 100.0f);
    _hitbox.setPosition(_position.x * window.getSize().x / 100.0f, _position.y * window.getSize().y / 100.0f);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}