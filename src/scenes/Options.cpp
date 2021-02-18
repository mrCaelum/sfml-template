#include "Options.hpp"

Options::Options(sf::RenderWindow const &window, RessourcesHandler &ressources) : Scene{},
_rangePicker{
    10U,
    {100.0f, 100.0f},
    {500.0f, 20.0f}
},
_switch{
    {100.0f, 200.0f},
    {20.0f}
},
_backBtn{
    "back",
    ressources.getFont("assets/fonts/Roboto.ttf"),
    {window.getSize().x / 20.0f, 19 * window.getSize().y / 20.0f},
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.1f,
    TextButton::Origin::RIGHT,
    Animation{Animation::Type::RIGHT_TO_LEFT_SLIDE},
    Animation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
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
    _rangePicker.update(window);
    _switch.update(window, elapsed_time);
    _backBtn.update(window, elapsed_time);
}

void Options::draw(sf::RenderWindow &window)
{
    window.draw(_rangePicker);
    window.draw(_switch);
    window.draw(_backBtn);
}