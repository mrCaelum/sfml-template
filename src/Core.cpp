#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Core.hpp"
#include "MenuScene.hpp"
#include "OptionsScene.hpp"
#include "GameScene.hpp"

Core::Core(Settings const &settings) noexcept
: _window{settings.videomode, "sfml-template", settings.getStyle(), settings.getContextSettings()}, _clock{}, _ressources{}, _currentScene{Scene::MENU}
{
	_window.setFramerateLimit(settings.framerate_limit);

	_ressources.setFont("assets/fonts/Roboto.ttf");
	_ressources.setSound("assets/audio/select.wav");
	_ressources.setTexture("assets/background.jpg");

	_scenes.push_back(std::make_unique<Scenes::Menu>(_window, _ressources));
	_scenes.push_back(std::make_unique<Scenes::Options>(_window, _ressources));
	_scenes.push_back(std::make_unique<Scenes::Game>(_window, _ressources));
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