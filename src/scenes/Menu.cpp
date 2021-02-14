#include "Menu.hpp"

Menu::Menu(sf::RenderWindow const &window, sf::Font const &font)
: Scene{}
, _textMenu{
    font,
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.5f,
    TextButton::AnimationType::LEFT_TO_RIGHT_SLIDE,
    0.1f,
    1.2f,
    100U
} {
    _textMenu.addButton("Play", {window.getSize().x / 10.0f, 11 * window.getSize().y / 20.0f});
    _textMenu.addButton("Exit", {window.getSize().x / 10.0f, 12 * window.getSize().y / 20.0f});
}

void Menu::event(sf::RenderWindow &window, Scene::ID &currentId)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        _textMenu.updateStates(window, event);
        if (_textMenu.getButton("Exit")->getState() == TextButton::State::RELEASED)
            window.close();
        if (_textMenu.getButton("Play")->getState() == TextButton::State::RELEASED)
            currentId = Scene::ID::GAME;
    }
}

void Menu::update(sf::RenderWindow &window, const float elapsedTime)
{
    _textMenu.update(window, elapsedTime);
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(_textMenu);
}