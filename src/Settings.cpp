#include <string>
#include <fstream>
#include "Settings.hpp"

Settings::Settings(sf::VideoMode const &videomode, unsigned int framerate_limit, bool fullscreen, unsigned int antialiasing_level)
: videomode{videomode}, framerate_limit{framerate_limit}, fullscreen{fullscreen}, antialiasing_level{antialiasing_level} {}

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
        } else if (key == "fullscreen") {
            fullscreen = value == "true";
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
    file << "fullscreen=" << (fullscreen ? "true" : "false") << std::endl;
    file << "antialiasing-level=" << antialiasing_level << std::endl;
    file.close();
}

std::string Settings::getResolution() const
{
    return std::to_string(videomode.width) + "x" + std::to_string(videomode.height);
}

unsigned int Settings::getStyle() const
{
    return fullscreen ? sf::Style::Fullscreen : sf::Style::Close;
}

sf::ContextSettings Settings::getContextSettings() const
{
    return sf::ContextSettings{0, 0, antialiasing_level};
}

void Settings::apply(Settings const &settings, sf::RenderWindow &window)
{
    if (videomode != settings.videomode || fullscreen != settings.fullscreen || antialiasing_level != settings.antialiasing_level) {
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

Settings &Settings::operator=(Settings const &other)
{
    videomode = other.videomode;
    framerate_limit = other.framerate_limit;
    fullscreen = other.fullscreen;
    antialiasing_level = other.antialiasing_level;

    return *this;
}