#include <iostream>
#include <fstream>
#include "Settings.hpp"

static sf::VideoMode strToResolution(std::string const &str)
{
    std::string x{str.substr(0, str.find('x'))};
    std::string y{str.substr(str.find('x') + 1, str.size())};

    return sf::VideoMode{static_cast<unsigned int>(std::strtoul(x.c_str(), nullptr, 0)), static_cast<unsigned int>(std::strtoul(y.c_str(), nullptr, 0))};
}

Settings::Settings(sf::VideoMode const &videomode, sf::String const &title, unsigned int framerate_limit, unsigned int style, sf::ContextSettings const &settings)
: videomode{videomode}, title{title}, framerate_limit{framerate_limit}, style{style}, settings{settings} {}

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
            style = (value == "true" ? sf::Style::Fullscreen : sf::Style::Close);
        } else if (key == "antialiasing-level") {
            settings = sf::ContextSettings{0, 0, static_cast<unsigned int>(std::strtoul(value.c_str(), nullptr, 0))};
        }
    }
    file.close();
}

void Settings::saveToFile(std::string const &filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
        return;
    file << "resolution=" << videomode.width << 'x' << videomode.height << std::endl;
    file << "fps-limit=" << framerate_limit << std::endl;
    file << "fullscreen=" << (style == sf::Style::Fullscreen ? "true" : "false") << std::endl;
    file << "antialiasing-level=" << settings.antialiasingLevel << std::endl;
    file.close();
}

void Settings::update(sf::RenderWindow &window) const
{}