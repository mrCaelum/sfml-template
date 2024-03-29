#pragma once

#include <string>
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Settings.hpp"
#include "Scene.hpp"
#include "RessourcesHandler.hpp"

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
        sf::Clock _clock;
        RessourcesHandler _ressources;
        std::vector<std::unique_ptr<Scene>> _scenes;
        Scene::ID _currentScene;
};