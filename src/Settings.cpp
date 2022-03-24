#include <string>
#include <fstream>
#include "Settings.hpp"

const sf::String Settings::WINDOW_TYPES[3] = {"Windowed", "Borderless", "Fullscreen"};

Settings::Settings(sf::VideoMode const &videomode, unsigned int framerate_limit, WindowType window_type, unsigned int antialiasing_level)
: videomode{videomode}, framerate_limit{framerate_limit}, window_type{window_type}, antialiasing_level{antialiasing_level} {}

void Settings::loadFromFile(std::string const &filename)
{
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
		return;
	while (std::getline(file, line)) {
		std::string key{line.substr(0, line.find('='))};
		std::string value{line.substr(line.find('=') + 1, line.size())};
		
		if (key == "resolution") {
			videomode = strToResolution(value);
		} else if (key == "fps-limit") {
			framerate_limit = std::strtoul(value.c_str(), nullptr, 0);
		} else if (key == "window-type") {
			window_type = static_cast<WindowType>(std::strtoul(value.c_str(), nullptr, 0));
		} else if (key == "antialiasing-level") {
			antialiasing_level = static_cast<unsigned int>(std::strtoul(value.c_str(), nullptr, 0));
		}
	}
	file.close();
}

void Settings::saveToFile(std::string const &filename) const
{
	std::ofstream file(filename);

	if (!file.is_open())
		return;
	file << "resolution=" << videomode.width << 'x' << videomode.height << std::endl;
	file << "fps-limit=" << framerate_limit << std::endl;
	file << "window-type=" << window_type << std::endl;
	file << "antialiasing-level=" << antialiasing_level << std::endl;
	file.close();
}

std::string Settings::getResolution() const
{
	return std::to_string(videomode.width) + "x" + std::to_string(videomode.height);
}

unsigned int Settings::getStyle() const
{
	switch (window_type) {
		case WindowType::WINDOWED:
			return sf::Style::Close;
		case WindowType::BORDERLESS:
			return sf::Style::None;
		case WindowType::FULLSCREEN:
			return sf::Style::Fullscreen;
	}
	return sf::Style::Close;
}

sf::ContextSettings Settings::getContextSettings() const
{
	return sf::ContextSettings{0, 0, antialiasing_level};
}

void Settings::apply(Settings const &settings, sf::RenderWindow &window)
{
	if (videomode != settings.videomode || window_type != settings.window_type || antialiasing_level != settings.antialiasing_level) {
		window.create(settings.videomode, "sfml-template", settings.getStyle(), settings.getContextSettings());
		window.setFramerateLimit(settings.framerate_limit);
	} else if (framerate_limit != settings.framerate_limit) {
		window.setFramerateLimit(settings.framerate_limit);
	}
	*this = settings;
}

sf::VideoMode Settings::strToResolution(std::string const &str)
{
	std::string x{str.substr(0, str.find('x'))};
	std::string y{str.substr(str.find('x') + 1, str.size())};

	return sf::VideoMode{static_cast<unsigned int>(std::strtoul(x.c_str(), nullptr, 0)), static_cast<unsigned int>(std::strtoul(y.c_str(), nullptr, 0))};
}

Settings::WindowType Settings::strToWindowType(std::string const &str)
{
	for (unsigned int i = 0; i < 3; ++i) {
		if (str == WINDOW_TYPES[i]) {
			return static_cast<WindowType>(i);
		}
	}
	return WindowType::WINDOWED;
}

Settings &Settings::operator=(Settings const &other)
{
	videomode = other.videomode;
	framerate_limit = other.framerate_limit;
	window_type = other.window_type;
	antialiasing_level = other.antialiasing_level;

	return *this;
}