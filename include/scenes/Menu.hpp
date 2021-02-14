#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <SFML/Graphics/Texture.hpp>
    #include <SFML/Graphics/Sprite.hpp>
    #include <SFML/Graphics/Font.hpp>
    #include "Scene.hpp"
    #include "TextButton.hpp"

    class Menu : public Scene
    {
    private:
        TextButton _playBtn;
        TextButton _exitBtn;

    public:
        Menu(sf::RenderWindow const &window, sf::Font const &font);
        ~Menu() = default;

        void event(sf::RenderWindow &window, Scene::ID &currentId) final;
        void update(sf::RenderWindow &window, const float elapsedTime) final;
        void draw(sf::RenderWindow &window) final;
    };
#endif