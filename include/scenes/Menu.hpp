#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Core.hpp"
#include "Scene.hpp"
#include "components/TextMenu.hpp"

namespace Scenes {
	class Menu : public Scene
	{
	private:
		sf::Text _title;
		TextMenu _textMenu;
		sf::Sound _selectSoundEffect;
		sf::Sprite _background;

	public:
		Menu();
		Menu(Menu const &other) = delete;
		~Menu() = default;
		Menu &operator=(Menu const &other) = delete;

		void event() final;
		void update(const float elapsedTime) final;
		void draw() final;
	};
};