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
        sf::VideoMode const &videomode,
        sf::String const &title = "undefined",
        unsigned int framerate_limit = 0U,
        unsigned int style = sf::Style::Default,
        sf::ContextSettings const &settings = sf::ContextSettings()
    );
    Settings() = delete;
    ~Settings() = default;

    void loadFromFile(sf::String const &filename);
    void saveToFile(sf::String const &filename);

    void setVideoMode(sf::String const &videoMode);

    void update(sf::RenderWindow &window) const;
};