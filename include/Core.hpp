#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <string>
    #include <memory>
    #include <vector>
    #include <SFML/System/Vector2.hpp>
    #include <SFML/Graphics/Font.hpp>
    #include "Scene.hpp"

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
            Core(sf::VideoMode video, sf::String title, unsigned int framerate = 60U, unsigned int style = sf::Style::Default, sf::ContextSettings const &settings = sf::ContextSettings()) noexcept;
            Core(Core const &other) = delete;
            ~Core() = default;
            int run();
        private:
            sf::RenderWindow _window;
            sf::Clock _clock;
            sf::Font _font;
            std::vector<std::unique_ptr<Scene>> _scenes;
            Scene::ID _currentScene;
    };
#endif