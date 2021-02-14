#include <fstream>
#include <iostream>
#include "Game.hpp"

Game::Game(sf::RenderWindow const &window) : Scene{}, _elapsedTime{0.0f}//, _player{window, {10.0f, 10.0f}}
{}

void Game::event(sf::RenderWindow &window, Scene::ID &currentId)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(sf::RenderWindow &window, const float elapsedTime)
{
    _elapsedTime += elapsedTime;
    while (_elapsedTime > 0.01f) {
        _elapsedTime -= 0.01f;
    }
}

void Game::draw(sf::RenderWindow &window)
{
    // window.draw(_player);
}