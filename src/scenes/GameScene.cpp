#include "GameScene.hpp"

Scenes::Game::Game(sf::RenderWindow &window, ResourcesHandler &resources) : Scene{window, resources}, _elapsedTime{0.0f}//, _player{window, {10.0f, 10.0f}}
{}

void Scenes::Game::event()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == sf::Keyboard::Escape)
				this->close();
	}
}

void Scenes::Game::update(const float elapsedTime)
{
	_elapsedTime += elapsedTime;
	while (_elapsedTime > 0.01f) {
		_elapsedTime -= 0.01f;
	}
}

void Scenes::Game::draw()
{
	// window.draw(_player);
}