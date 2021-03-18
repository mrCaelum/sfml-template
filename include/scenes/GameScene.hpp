#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "Scene.hpp"
#include "RessourcesHandler.hpp"

namespace Scenes {

    class Game : public Scene
    {
    private:
        float _elapsedTime;

    public:
        Game(sf::RenderWindow const &window, RessourcesHandler &ressources);
        ~Game() = default;

        void event(sf::RenderWindow &window, Scene::ID &currentId) final;
        void update(sf::RenderWindow &window, const float elapsedTime) final;
        void draw(sf::RenderWindow &window) final;
    };

};