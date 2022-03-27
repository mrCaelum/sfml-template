#include "scenes/OptionsScene.hpp"
#include "Settings.hpp"

Scenes::Options::Options(sf::RenderWindow &window, ResourcesHandler &resources)
: Scene{window, resources},
_categories_menu{
	_resources.getFont("Roboto"),
	30U,
	sf::Color::White,
	sf::Color::Black,
	0.5f,
	TextButton::Origin::LEFT,
	Animation{Animation::Type::LEFT_TO_RIGHT_SLIDE, 0.1f, 2.0f},
	Animation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
},
_rangePicker{
	10U,
	{300.0f, 100.0f},
	{500.0f, 20.0f}
},
_window_type_dropdown{
	_resources.getFont("Roboto"),
	"Select",
	{300.0f, 200.0f},
	{250.0f, 40.0f},
	{250.0f, 40.0f * 3.0f}
},
_resolutions_dropdown{
	_resources.getFont("Roboto"),
	"Select",
	{300.0f, 300.0f},
	{250.0f, 40.0f},
	{250.0f, 40.0f * 9.0f}
},
_apply_button{
	_resources.getFont("Roboto"),
	"Apply",
	{300.0f, 400.0f},
	{200.0f, 40.0f},
	24u,
	sf::Color{255, 255, 255},
	sf::Color{80, 80, 80},
	sf::Color{52, 152, 219},
	1.0f,
	Animation{},
	Animation{}
},
_back_button{
	_resources.getFont("Roboto"),
	"back",
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
	_categories_menu.addButton("Video", {100.0f, 10.0f + window.getSize().y / 10.0f});
	_categories_menu.addButton("Audio", {100.0f, 10.0f + window.getSize().y / 10.0f * 2.0f});

	for (unsigned char i = 0; i < 3; ++i) {
		_window_type_dropdown.addElement(Settings::WINDOW_TYPES[i]);
	}

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

	_window_type_dropdown.setValue(Settings::WINDOW_TYPES[GLOBAL_SETTINGS.window_type]);
	_resolutions_dropdown.setValue(GLOBAL_SETTINGS.getResolution());
}

void Scenes::Options::event()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == sf::Keyboard::Escape)
				this->close();
		_categories_menu.updateStates(_window, event);
		_back_button.updateState(_window, event);
		if (_back_button.getState() == TextButton::State::RELEASED)
			this->close();
	}
}

void Scenes::Options::update(const float elapsed_time)
{
	bool window_type_unwrapped = _window_type_dropdown.unwrapped();
	bool resolutions_unwrapped = _resolutions_dropdown.unwrapped();
	if (!window_type_unwrapped && !resolutions_unwrapped) {
		_categories_menu.update(_window, elapsed_time);
		_rangePicker.update(_window);
	}
	if (!resolutions_unwrapped) {
		_window_type_dropdown.update(_window, elapsed_time);
	}
	Settings::WindowType window_type = Settings::strToWindowType(_window_type_dropdown.getValue());
	if (!window_type_unwrapped) {
		_resolutions_dropdown.disabled = window_type == Settings::WindowType::FULLSCREEN;
		_resolutions_dropdown.update(_window, elapsed_time);
	}
	sf::VideoMode resolution = Settings::strToResolution(_resolutions_dropdown.getValue());
	if (!window_type_unwrapped && !resolutions_unwrapped) {
		_apply_button.disabled = window_type == GLOBAL_SETTINGS.window_type && resolution == GLOBAL_SETTINGS.videomode;
		_apply_button.update(_window, elapsed_time);
		_back_button.update(elapsed_time);
		if (_apply_button.released()) {
			Settings settings{
				resolution,
				60U,
				window_type,
				8U
			};
			GLOBAL_SETTINGS.apply(settings, _window);
			GLOBAL_SETTINGS.saveToFile(SETTINGS_FILE);
		}
	}
}

void Scenes::Options::draw()
{
	_window.draw(_categories_menu);
	_window.draw(_rangePicker);
	_window.draw(_apply_button);
	_window.draw(_back_button);
	_window.draw(_resolutions_dropdown);
	_window.draw(_window_type_dropdown);
}