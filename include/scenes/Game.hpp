#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "Scene.hpp"
// #include "Player.hpp"

class Game : public Scene
{
private:
    // Player _player;
    float _elapsedTime;

public:
    Game(sf::RenderWindow const &window);
    ~Game() = default;

    void event(sf::RenderWindow &window, Scene::ID &currentId) final;
    void update(sf::RenderWindow &window, const float elapsedTime) final;
    void draw(sf::RenderWindow &window) final;
};

#endif