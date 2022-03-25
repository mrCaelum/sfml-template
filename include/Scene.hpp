#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "ResourcesHandler.hpp"

#define OPEN_SCENE(type, window, resources) do{type __SCENE__(window, resources); __SCENE__.play();}while(0)

class Scene
{
public:
	Scene(sf::RenderWindow &window, ResourcesHandler &resources) noexcept;
	Scene(Scene const &) = delete;
	~Scene() = default;

	bool isAlive() const noexcept;
	void close() noexcept;
	void play();

	virtual void event();
	virtual void update(const float elapsedTime) = 0;
	virtual void draw() = 0;

protected:
	sf::RenderWindow &_window;
	ResourcesHandler &_resources;

private:
	bool _alive;
	sf::Clock _clock;
};