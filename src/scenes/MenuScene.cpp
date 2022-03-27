#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "OptionsScene.hpp"

Scenes::Menu::Menu(sf::RenderWindow &window, ResourcesHandler &resources)
: Scene{window, resources}, _title{"Platformer", _resources.getFont("Roboto"), 50U}
, _textMenu{
	_resources.getFont("Roboto"),
	30U,
	sf::Color::White,
	sf::Color::Black,
	0.5f,
	TextButton::Origin::LEFT,
	Animation{Animation::Type::LEFT_TO_RIGHT_SLIDE, 0.1f, 2.0f},
	Animation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
}, _selectSoundEffect{_resources.getSound("select")}, _background{}
{
	_title.setPosition({window.getSize().x / 2.0f, window.getSize().y / 5.0f});
	_title.setFillColor(sf::Color::White);
	_title.setOutlineColor(sf::Color::Black);
	_title.setOutlineThickness(1.0f);
	_title.setCharacterSize(70U);
	_title.setOrigin({_title.getGlobalBounds().width / 2.0f, _title.getGlobalBounds().height / 2.0f});

	_textMenu.addButton("Play", {window.getSize().x / 10.0f, 11 * window.getSize().y / 20.0f});
	_textMenu.addButton("Options", {window.getSize().x / 10.0f, 12 * window.getSize().y / 20.0f});
	_textMenu.addButton("Exit", {window.getSize().x / 10.0f, 13 * window.getSize().y / 20.0f});

	_background.setTexture(_resources.getTexture("background"));
}

void Scenes::Menu::event()
{
	static bool _sound_effect_played = false;
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window.close();
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();

		_textMenu.updateStates(_window, event);
		TextButton::State playBtnState = _textMenu.getButton("Play")->getState(), optionsBtnState = _textMenu.getButton("Options")->getState(), exitBtnState = _textMenu.getButton("Exit")->getState();
		if (exitBtnState == TextButton::State::RELEASED)
			_window.close();
		if (playBtnState == TextButton::State::RELEASED)
			OPEN_SCENE(Scenes::Game, _window, _resources);
		if (optionsBtnState == TextButton::State::RELEASED)
			OPEN_SCENE(Scenes::Options, _window, _resources);
		if (playBtnState == TextButton::State::HOVERED || optionsBtnState == TextButton::State::HOVERED || exitBtnState == TextButton::State::HOVERED) {
			if (!_sound_effect_played && _selectSoundEffect.getStatus() != sf::Sound::Status::Playing) {
				_selectSoundEffect.play();
			}
			_sound_effect_played = true;
		} else {
			_sound_effect_played = false;
		}
	}
}

void Scenes::Menu::update(const float elapsedTime)
{
	_textMenu.update(_window, elapsedTime);
}

void Scenes::Menu::draw()
{
	_window.draw(_background);
	_window.draw(_title);
	_window.draw(_textMenu);
}