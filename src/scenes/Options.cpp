#include "Options.hpp"

Options::Options(sf::RenderWindow const &window, RessourcesHandler &ressources) : Scene{},
_rangePicker{
    10U,
    {100.0f, 100.0f},
    {500.0f, 20.0f}
},
_switch{
    {100.0f, 200.0f},
    {25.0f}
},
_resolutions_dropdown{
    ressources.getFont("assets/fonts/Roboto.ttf"),
    "Select",
    {100.0f, 300.0f},
    {250.0f, 40.0f},
    {250.0f, 40.0f * 9.0f}
},
_apply_button{
    ressources.getFont("assets/fonts/Roboto.ttf"),
    "Apply",
    {100.0f, 400.0f}
},
_back_button{
    "back",
    ressources.getFont("assets/fonts/Roboto.ttf"),
    {window.getSize().x / 20.0f, 19 * window.getSize().y / 20.0f},
    30U,
    sf::Color::White,
    sf::Color::Black,
    0.1f,
    TextButton::Origin::RIGHT,
    Animation{Animation::Type::RIGHT_TO_LEFT_SLIDE, 0.1f, 2.0f},
    Animation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
}
{
    // 4:3
    // _resolutions_dropdown.addElement("640x480");
    // _resolutions_dropdown.addElement("800x600");
    // _resolutions_dropdown.addElement("960x720");
    // _resolutions_dropdown.addElement("1024x768");
    // _resolutions_dropdown.addElement("1280x960");
    // _resolutions_dropdown.addElement("1400x1050");
    // _resolutions_dropdown.addElement("1440x1080");
    // _resolutions_dropdown.addElement("1600x1200");
    // _resolutions_dropdown.addElement("1856x1392");
    // _resolutions_dropdown.addElement("1920x1440");
    // _resolutions_dropdown.addElement("2048x1536");

    // 16:10
    // _resolutions_dropdown.addElement("1280x800");
    // _resolutions_dropdown.addElement("1440x900");
    // _resolutions_dropdown.addElement("1680x1050");
    // _resolutions_dropdown.addElement("1920x1200");
    // _resolutions_dropdown.addElement("2560x1600");

    // 16:9
    _resolutions_dropdown.addElement("1024x576");
    _resolutions_dropdown.addElement("1152x648");
    _resolutions_dropdown.addElement("1280x720");
    _resolutions_dropdown.addElement("1366x768");
    _resolutions_dropdown.addElement("1600x900");
    _resolutions_dropdown.addElement("1920x1080");
    _resolutions_dropdown.addElement("2560x1440");
    _resolutions_dropdown.addElement("3840x2160");
    _resolutions_dropdown.addElement("7680x4320");
}

void Options::event(sf::RenderWindow &window, Scene::ID &currentId)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == sf::Keyboard::Escape)
                currentId = Scene::ID::MENU;
        _back_button.updateState(window, event);
        if (_back_button.getState() == TextButton::State::RELEASED)
            currentId = Scene::ID::MENU;
    }
}

void Options::update(sf::RenderWindow &window, const float elapsed_time)
{
    _rangePicker.update(window);
    _switch.update(window, elapsed_time);
    _resolutions_dropdown.update(window, elapsed_time);
    _apply_button.update(window, elapsed_time);
    _back_button.update(window, elapsed_time);
}

void Options::draw(sf::RenderWindow &window)
{
    window.draw(_rangePicker);
    window.draw(_switch);
    window.draw(_resolutions_dropdown);
    window.draw(_apply_button);
    window.draw(_back_button);
}