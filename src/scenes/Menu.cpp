#include "Menu.hpp"

Menu::Menu(sf::RenderWindow const &window, sf::Font const &font)
: Scene{}, _title{"Platformer", font, 50U}, _selectSoundEffect{"assets/audio/select.wav"}
, _textMenu{
    font,
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.5f,
    TextButton::Origin::LEFT,
    TextAnimation{Animation::Type::LEFT_TO_RIGHT_SLIDE},
    TextAnimation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
} {
    _title.setPosition({window.getSize().x / 2.0f, window.getSize().y / 5.0f});
    _title.setFillColor(sf::Color::White);
    _title.setOutlineColor(sf::Color::Black);
    _title.setOutlineThickness(0.1f);
    _title.setOrigin({_title.getGlobalBounds().width / 2.0f, _title.getGlobalBounds().height / 2.0f});

    _textMenu.addButton("Play", {window.getSize().x / 10.0f, 11 * window.getSize().y / 20.0f});
    _textMenu.addButton("Options", {window.getSize().x / 10.0f, 12 * window.getSize().y / 20.0f});
    _textMenu.addButton("Exit", {window.getSize().x / 10.0f, 13 * window.getSize().y / 20.0f});
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
        TextButton::State playBtnState = _textMenu.getButton("Play")->getState(), optionsBtnState = _textMenu.getButton("Options")->getState(), exitBtnState = _textMenu.getButton("Exit")->getState();
        if (exitBtnState == TextButton::State::RELEASED)
            window.close();
        if (playBtnState == TextButton::State::RELEASED)
            currentId = Scene::ID::GAME;
        if (optionsBtnState == TextButton::State::RELEASED)
            currentId = Scene::ID::OPTIONS;
        if (playBtnState == TextButton::State::HOVERED || optionsBtnState == TextButton::State::HOVERED || exitBtnState == TextButton::State::HOVERED) {
            _selectSoundEffect.play();
        } else
            _selectSoundEffect.reset();
    }
}

void Menu::update(sf::RenderWindow &window, const float elapsedTime)
{
    _textMenu.update(window, elapsedTime);
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(_title);
    window.draw(_textMenu);
}