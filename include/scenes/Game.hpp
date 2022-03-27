#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Core.hpp"
#include "Scene.hpp"

namespace Scenes {
	class Game : public Scene
	{
	private:
		float _elapsedTime;

	public:
		Game();
		Game(Game const &other) = delete;
		~Game() = default;
		Game &operator=(Game const &other) = delete;

		void event() final;
		void update(const float elapsedTime) final;
		void draw() final;
	};
};