#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Settings
{
public:
    sf::VideoMode videomode;
    sf::String title;
    unsigned int framerate_limit;
    unsigned int style;
    sf::ContextSettings settings;

    Settings(
        sf::VideoMode const &videomode = sf::VideoMode{1920U, 1080U},
        sf::String const &title = "undefined",
        unsigned int framerate_limit = 0U,
        unsigned int style = sf::Style::Default,
        sf::ContextSettings const &settings = sf::ContextSettings()
    );
    ~Settings() = default;

    void loadFromFile(std::string const &filename);
    void saveToFile(std::string const &filename);

    void update(sf::RenderWindow &window) const;
};