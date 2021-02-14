#include "Menu.hpp"

Menu::Menu(sf::RenderWindow const &window, sf::Font const &font)
: Scene{}
, _playBtn{
    "Play",
    font,
    {window.getSize().x / 2.0f, window.getSize().y / 2.0f},
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.5f,
    TextButton::AnimationType::ZOOM_IN,
    0.1f,
    1.2f,
    100U
}, _exitBtn{
    "Exit",
    font,
    {window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50.0f},
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.5f,
    TextButton::AnimationType::ZOOM_IN,
    0.1f,
    1.2f,
    100U
} {}

void Menu::event(sf::RenderWindow &window, Scene::ID &currentId)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        _playBtn.updateState(window, event);
        _exitBtn.updateState(window, event);
    }
}

void Menu::update(sf::RenderWindow &window, const float elapsedTime)
{
    _playBtn.update(window, elapsedTime);
    _exitBtn.update(window, elapsedTime);
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(_playBtn);
    window.draw(_exitBtn);
}