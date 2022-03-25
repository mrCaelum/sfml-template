#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Scene.hpp"
#include "ResourcesHandler.hpp"
#include "TextMenu.hpp"
#include "TextButton.hpp"
#include "Button.hpp"
#include "RangePicker.hpp"
#include "Switch.hpp"
#include "TextDropdown.hpp"

namespace Scenes {
	class Options : public Scene
	{
	private:
		TextMenu _categories_menu;
		RangePicker _rangePicker;
		TextDropdown _window_type_dropdown;
		TextDropdown _resolutions_dropdown;
		Button _apply_button;
		TextButton _back_button;

	public:
		Options(sf::RenderWindow &window, ResourcesHandler &resources);
		~Options() = default;

		void event() final;
		void update(const float elapsed_time) final;
		void draw() final;
	};
};