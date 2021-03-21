#include "OptionsScene.hpp"
#include "Settings.hpp"

Scenes::Options::Options(sf::RenderWindow const &window, RessourcesHandler &ressources) : Scene{},
_rangePicker{
    10U,
    {100.0f, 100.0f},
    {500.0f, 20.0f}
},
_fullscreen_switch{
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

    _fullscreen_switch.check(GLOBAL_SETTINGS.fullscreen);
    _resolutions_dropdown.setValue(GLOBAL_SETTINGS.getResolution());
}

void Scenes::Options::event(sf::RenderWindow &window, Scene::ID &currentId)
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

void Scenes::Options::update(sf::RenderWindow &window, const float elapsed_time)
{
    _rangePicker.update(window);
    _fullscreen_switch.update(window, elapsed_time);
    _resolutions_dropdown.update(window, elapsed_time);
    _apply_button.update(window, elapsed_time);
    _back_button.update(window, elapsed_time);
    if (_apply_button.released()) {
        Settings settings{
            Settings::strToResolution(_resolutions_dropdown.getValue()),
            60U,
            _fullscreen_switch.checked(),
            8U
        };
        GLOBAL_SETTINGS.apply(settings, window);
        GLOBAL_SETTINGS.saveToFile(SETTINGS_FILE);
    }
}

void Scenes::Options::draw(sf::RenderWindow &window)
{
    window.draw(_rangePicker);
    window.draw(_fullscreen_switch);
    window.draw(_apply_button);
    window.draw(_back_button);
    window.draw(_resolutions_dropdown);
}