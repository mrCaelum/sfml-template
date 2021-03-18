#include <iostream>
#include <fstream>
#include "Settings.hpp"

Settings::Settings(sf::VideoMode const &videomode, sf::String const &title, unsigned int framerate_limit, unsigned int style, sf::ContextSettings const &settings)
: videomode{videomode}, title{title}, framerate_limit{framerate_limit}, style{style}, settings{settings} {}

void Settings::loadFromFile(sf::String const &filename)
{
    std::ifstream file(filename.toAnsiString());
    std::string line;

    if (!file.is_open())
        return;
    while (std::getline(file, line)) {
        std::string key{line.substr(0, line.find('='))};
        std::string value{line.substr(line.find('='), line.size())};
        std::cout << key << '=' << value << std::endl;
    }
    file.close();
}

void Settings::saveToFile(sf::String const &filename)
{}

void Settings::setVideoMode(sf::String const &videoMode)
{}

void Settings::update(sf::RenderWindow &window) const
{}