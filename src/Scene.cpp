#include <Scene.hpp>

Scene::Scene(sf::RenderWindow &window, ResourcesHandler &resources) noexcept
: _window{window}, _resources{resources}, _alive{true}, _clock{}
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
	while (_window.isOpen() && this->isAlive()) {
		this->event();
		this->update(_clock.restart().asSeconds());
		_window.clear();
		this->draw();
		_window.display();
	}
}

void Scene::event()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
	}
}