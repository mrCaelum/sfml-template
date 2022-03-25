#pragma once

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Settings.hpp"
#include "Scene.hpp"
#include "ResourcesHandler.hpp"

namespace sf {
	class VideoMode;
	class String;
	class RenderWindow;
	class Clock;
	class Font;
};

class Core {
	public:
		Core() = delete;
		Core(Settings const &settings) noexcept;
		Core(Core const &other) = delete;
		~Core() = default;
		int run();

	private:
		sf::RenderWindow _window;
		ResourcesHandler _resources;
};