#include "scenes/Menu.hpp"
#include "scenes/Game.hpp"
#include "scenes/Options.hpp"

Scenes::Menu::Menu()
: _title{"sfml-template", Core::RESOURCES.getFont("Roboto"), 50U}
, _textMenu{
	Core::RESOURCES.getFont("Roboto"),
	30U,
	sf::Color::White,
	sf::Color::Black,
	0.5f,
	TextButton::Origin::LEFT,
	Animation{Animation::Type::LEFT_TO_RIGHT_SLIDE, 0.1f, 2.0f},
	Animation{Animation::Type::ZOOM_OUT, 0.05f, 1.05f}
}, _selectSoundEffect{Core::RESOURCES.getSound("select")}, _background{}
{
	_title.setPosition({Core::WINDOW.getSize().x / 2.0f, Core::WINDOW.getSize().y / 5.0f});
	_title.setFillColor(sf::Color::White);
	_title.setOutlineColor(sf::Color::Black);
	_title.setOutlineThickness(1.0f);
	_title.setCharacterSize(70U);
	_title.setOrigin({_title.getGlobalBounds().width / 2.0f, _title.getGlobalBounds().height / 2.0f});

	_textMenu.addButton("Play", {Core::WINDOW.getSize().x / 10.0f, 11 * Core::WINDOW.getSize().y / 20.0f});
	_textMenu.addButton("Options", {Core::WINDOW.getSize().x / 10.0f, 12 * Core::WINDOW.getSize().y / 20.0f});
	_textMenu.addButton("Exit", {Core::WINDOW.getSize().x / 10.0f, 13 * Core::WINDOW.getSize().y / 20.0f});

	_background.setTexture(Core::RESOURCES.getTexture("background"));
}

void Scenes::Menu::event()
{
	static bool _sound_effect_played = false;
	sf::Event event;

	while (Core::WINDOW.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			Core::WINDOW.close();
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == sf::Keyboard::Escape)
				Core::WINDOW.close();

		_textMenu.updateStates(event);
		TextButton::State playBtnState = _textMenu.getButton("Play")->getState(), optionsBtnState = _textMenu.getButton("Options")->getState(), exitBtnState = _textMenu.getButton("Exit")->getState();
		if (exitBtnState == TextButton::State::RELEASED)
			Core::WINDOW.close();
		if (playBtnState == TextButton::State::RELEASED)
			OPEN_SCENE(Scenes::Game);
		if (optionsBtnState == TextButton::State::RELEASED)
			OPEN_SCENE(Scenes::Options);
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
	_textMenu.update(elapsedTime);
}

void Scenes::Menu::draw()
{
	Core::WINDOW.draw(_background);
	Core::WINDOW.draw(_title);
	Core::WINDOW.draw(_textMenu);
}