#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Core.hpp"
#include "scenes/MenuScene.hpp"

Core::Core(Settings const &settings) noexcept
: _window{settings.videomode, "sfml-template", settings.getStyle(), settings.getContextSettings()}, _resources{}
{
	_window.setFramerateLimit(settings.framerate_limit);

	_resources.setFont("assets/fonts/Roboto.ttf", "Roboto");
	_resources.setSound("assets/audio/select.wav", "select");
	_resources.setTexture("assets/background.jpg", "background");
}

int Core::run()
{
	OPEN_SCENE(Scenes::Menu, _window, _resources);

	return EXIT_SUCCESS;
}