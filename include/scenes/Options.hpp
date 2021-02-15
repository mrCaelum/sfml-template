#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Scene.hpp"
#include "RessourcesHandler.hpp"
#include "TextButton.hpp"

class Options : public Scene
{
private:
    TextButton _backBtn;
public:
    Options(sf::RenderWindow const &window, RessourcesHandler &ressources);
    ~Options() = default;

    void event(sf::RenderWindow &window, Scene::ID &currentId) final;
    void update(sf::RenderWindow &window, const float elapsed_time) final;
    void draw(sf::RenderWindow &window) final;
};