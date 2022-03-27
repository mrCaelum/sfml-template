#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Core.hpp"
#include "Scene.hpp"
#include "components/TextMenu.hpp"
#include "components/TextButton.hpp"
#include "components/Button.hpp"
#include "components/RangePicker.hpp"
#include "components/Switch.hpp"
#include "components/TextDropdown.hpp"

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
		Options();
		Options(Options const &other) = delete;
		~Options() = default;
		Options &operator=(Options const &other) = delete;

		void event() final;
		void update(const float elapsed_time) final;
		void draw() final;
	};
};