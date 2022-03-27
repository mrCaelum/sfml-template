#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#define OPEN_SCENE(type) do{ type __SCENE__; __SCENE__.play(); }while(0)

class Scene
{
protected:
	Scene() noexcept;

public:
	Scene(Scene const &) = delete;
	~Scene() = default;
	Scene &operator=(Scene const &other) = delete;

	bool isAlive() const noexcept;
	void close() noexcept;
	void play();

	virtual void event();
	virtual void update(const float elapsedTime) = 0;
	virtual void draw() = 0;

private:
	bool _alive;
	sf::Clock _clock;
};