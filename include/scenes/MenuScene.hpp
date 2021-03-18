#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Scene.hpp"
#include "RessourcesHandler.hpp"
#include "TextMenu.hpp"
#include "SoundEffect.hpp"

namespace Scenes {

    class Menu : public Scene
    {
    private:
        sf::Text _title;
        TextMenu _textMenu;
        SoundEffect _selectSoundEffect;
        sf::Sprite _background;

    public:
        Menu(sf::RenderWindow const &window, RessourcesHandler &ressources);
        ~Menu() = default;

        void event(sf::RenderWindow &window, Scene::ID &currentId) final;
        void update(sf::RenderWindow &window, const float elapsedTime) final;
        void draw(sf::RenderWindow &window) final;
    };

};