#ifndef SCENE_HPP_
    #define SCENE_HPP_

    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Window/Event.hpp>

    class Scene
    {
    public:
        enum ID {
            MENU,
            GAME
        };

        Scene() = default;
        Scene(Scene const &) = delete;
        ~Scene() = default;

        virtual void event(sf::RenderWindow &window, Scene::ID &currentId);
        virtual void update(sf::RenderWindow &window, const float elapsedTime) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
    };
#endif