#include "GameScene.hpp"

Scenes::Game::Game(sf::RenderWindow const &window, RessourcesHandler &ressources) : Scene{}, _elapsedTime{0.0f}//, _player{window, {10.0f, 10.0f}}
{}

void Scenes::Game::event(sf::RenderWindow &window, Scene::ID &currentId)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == sf::Keyboard::Escape)
                currentId = Scene::ID::MENU;
    }
}

void Scenes::Game::update(sf::RenderWindow &window, const float elapsedTime)
{
    _elapsedTime += elapsedTime;
    while (_elapsedTime > 0.01f) {
        _elapsedTime -= 0.01f;
    }
}

void Scenes::Game::draw(sf::RenderWindow &window)
{
    // window.draw(_player);
}