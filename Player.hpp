#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <SFML/Graphics.hpp>

    class Player : public sf::Drawable
    {
    private:
        sf::Vector2f _position;
        sf::Vector2f _velocity;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::CircleShape _hitbox;

    public:
        Player() = delete;
        Player(sf::RenderWindow const &window, sf::Vector2f const &position);
        ~Player() = default;

        void stop();
        void addVelocity(sf::Vector2f const &vector);
        void move(sf::Vector2f const &to);
        void setPosition(sf::Vector2f const &point);
        sf::Vector2f const &getPosition() const;

        bool contains(sf::Vector2f const &point) const;
        bool intersect(sf::RenderWindow const &window, sf::FloatRect const &object) const;
        bool intersect(sf::RenderWindow const &window, sf::RectangleShape const &object) const;

        void update(sf::RenderWindow const &window, bool const timed = false);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
#endif