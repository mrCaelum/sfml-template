#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#define SETTINGS_FILE "default.settings"

class Settings
{
public:
    sf::VideoMode videomode;
    unsigned int framerate_limit;
    bool fullscreen;
    unsigned int antialiasing_level;

    Settings(
        sf::VideoMode const &videomode = sf::VideoMode{1920U, 1080U},
        unsigned int framerate_limit = 0U,
        bool fullscreen = false,
        unsigned int antialiasing_level = 8U
    );
    ~Settings() = default;

    void loadFromFile(std::string const &filename);
    void saveToFile(std::string const &filename) const;

    std::string getResolution() const;
    unsigned int getStyle() const;
    sf::ContextSettings getContextSettings() const;

    void apply(Settings const &settings, sf::RenderWindow &window);

    static sf::VideoMode strToResolution(std::string const &str);

    Settings &operator=(Settings const &other);
};

extern Settings GLOBAL_SETTINGS;