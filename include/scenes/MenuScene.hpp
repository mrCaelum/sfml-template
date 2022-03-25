#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Scene.hpp"
#include "ResourcesHandler.hpp"
#include "TextMenu.hpp"

namespace Scenes {
	class Menu : public Scene
	{
	private:
		sf::Text _title;
		TextMenu _textMenu;
		sf::Sound _selectSoundEffect;
		sf::Sprite _background;

	public:
		Menu(sf::RenderWindow &window, ResourcesHandler &resources);
		~Menu() = default;

		void event() final;
		void update(const float elapsedTime) final;
		void draw() final;
	};
};