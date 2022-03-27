#include "scenes/Game.hpp"

Scenes::Game::Game()
: _elapsedTime{0.0f}
{}

void Scenes::Game::event()
{
	sf::Event event;

	while (Core::WINDOW.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Core::WINDOW.close();
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
{}