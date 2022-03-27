#include <Scene.hpp>
#include "Core.hpp"

Scene::Scene() noexcept
: _alive{true}, _clock{}
{}

bool Scene::isAlive() const noexcept
{
	return _alive;
}

void Scene::close() noexcept
{
	_alive = false;
}

void Scene::play()
{
	while (Core::WINDOW.isOpen() && this->isAlive()) {
		this->event();
		this->update(_clock.restart().asSeconds());
		Core::WINDOW.clear();
		this->draw();
		Core::WINDOW.display();
	}
}

void Scene::event()
{
	sf::Event event;

	while (Core::WINDOW.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Core::WINDOW.close();
	}
}