#ifndef TILE_HPP
    #define TILE_HPP

    #include <SFML/Graphics.hpp>

    class Tile : public sf::Drawable
    {
    private:
        sf::Vector2u _position;
        sf::Sprite _sprite;

    public:
        Tile() = delete;
        Tile(sf::RenderWindow const &window, sf::Vector2f const &position);
        ~Tile() = default;

        void stop();
        void addVelocity(sf::Vector2f const &vector);
        void move(sf::Vector2f const &to);
        void setPosition(sf::Vector2f const &point);
        sf::Vector2f const &getPosition() const;

        bool contains(sf::Vector2f const &point) const;
        bool intersect(sf::RenderWindow const &window, sf::FloatRect const &object) const;
        bool intersect(sf::RenderWindow const &window, sf::RectangleShape const &object) const;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
#endif