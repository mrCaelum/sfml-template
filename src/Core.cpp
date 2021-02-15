#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Core.hpp"
#include "Menu.hpp"
#include "Options.hpp"
#include "Game.hpp"

Core::Core(sf::VideoMode const video, sf::String const title, unsigned int framerate, unsigned int style, sf::ContextSettings const &settings) noexcept
: _window{video, title, style, settings}, _clock{}, _ressources{}, _currentScene{Scene::MENU}
{
    _window.setFramerateLimit(framerate);

    _ressources.setFont("assets/fonts/Roboto.ttf");
    _ressources.setSound("assets/audio/select.wav");
    _ressources.setTexture("assets/background.jpg");

    _scenes.push_back(std::make_unique<Menu>(_window, _ressources));
    _scenes.push_back(std::make_unique<Options>(_window, _ressources));
    _scenes.push_back(std::make_unique<Game>(_window, _ressources));
}

int Core::run()
{
    while (_window.isOpen()) {
        _scenes[_currentScene]->event(_window, _currentScene);
        _scenes[_currentScene]->update(_window, _clock.restart().asSeconds());
        _window.clear();
        _scenes[_currentScene]->draw(_window);
        _window.display();
    }
    return EXIT_SUCCESS;
}