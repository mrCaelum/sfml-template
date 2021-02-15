#include "Options.hpp"

Options::Options(sf::RenderWindow const &window, RessourcesHandler &ressources) : Scene{}
, _backBtn{
    "back",
    ressources.getFont("assets/fonts/Roboto.ttf"),
    {window.getSize().x / 20.0f, 19 * window.getSize().y / 20.0f},
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.1f,
    TextButton::Origin::RIGHT,
    TextAnimation{Animation::Type::RIGHT_TO_LEFT_SLIDE},
    TextAnimation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
}
{}

void Options::event(sf::RenderWindow &window, Scene::ID &currentId)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == sf::Keyboard::Escape)
                currentId = Scene::ID::MENU;
        _backBtn.updateState(window, event);
        if (_backBtn.getState() == TextButton::State::RELEASED)
            currentId = Scene::ID::MENU;
    }
}

void Options::update(sf::RenderWindow &window, const float elapsed_time)
{
    _backBtn.update(window, elapsed_time);
}

void Options::draw(sf::RenderWindow &window)
{
    window.draw(_backBtn);
}