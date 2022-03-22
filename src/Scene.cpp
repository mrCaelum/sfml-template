#include <Scene.hpp>

void Scene::event(sf::RenderWindow &window, Scene::ID &currentId)
{
	sf::Event evt;

	while (window.pollEvent(evt)) {
		if (evt.type == sf::Event::Closed)
			window.close();
	}
}