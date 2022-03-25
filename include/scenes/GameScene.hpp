#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "Scene.hpp"
#include "ResourcesHandler.hpp"

namespace Scenes {
	class Game : public Scene
	{
	private:
		float _elapsedTime;

	public:
		Game(sf::RenderWindow &window, ResourcesHandler &resources);
		~Game() = default;

		void event() final;
		void update(const float elapsedTime) final;
		void draw() final;
	};
};