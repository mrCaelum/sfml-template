#include <SFML/Window/Mouse.hpp>
#include "TextDropdown.hpp"

TextDropdownElement::TextDropdownElement(sf::Font const &font, sf::String const &text, sf::Vector2f const &size, unsigned int character_size)
: _size{size}, _text{}, _box{}
{
    _text.setFont(font);
    _text.setString(text);
    _text.setOrigin({0.0f, _text.getGlobalBounds().height / 2.0f});
    _text.setPosition({10.0f, size.y / 2.0f});
    _text.setFillColor(sf::Color(200, 200, 200));
    _text.setCharacterSize(character_size);

    _box.setSize(_size);
    _box.setFillColor(sf::Color(0, 0, 0, 0));
    _box.setOutlineColor(sf::Color(50, 50, 50, 50));
    _box.setOutlineThickness(1.0f);
}

sf::String TextDropdownElement::getValue() const
{
    return _text.getString();
}

void TextDropdownElement::setPosition(sf::Vector2f const &position)
{
    _box.setPosition(position);
    _text.setPosition(position.x + 10.0f, position.y + _size.y / 2.0f);
}

bool TextDropdownElement::update(sf::Vector2f const &mouse_position)
{
    if (_box.getGlobalBounds().contains(mouse_position)) {
        _box.setFillColor(sf::Color(50, 50, 50, 50));
        return true;
    }
    _box.setFillColor(sf::Color(0, 0, 0, 0));
    return false;
}

void TextDropdownElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_box, states);
    target.draw(_text, states);
}

TextDropdown::TextDropdown(sf::Font const &font, sf::String const &placeholder, sf::Vector2f const &position, sf::Vector2f const &size, sf::Vector2f const &dropdown_size, unsigned int character_size, sf::Color const &primary_color, sf::Color const &background_color, Animation const &arrow_clicked)
: _font{font}, _position{position}, _size{size}, _dropdown_size{dropdown_size}, _character_size{character_size}, _primary_color{primary_color}, _background_color{background_color}, _box{}, _arrow{size.y / 8.0f, 3}, _selectedText{}, _texture_frame{}, _frame{}, _elements{}, _arrow_clicked{arrow_clicked}, _state{State::IDLE}, _unwrapped{false}, _changed{false}
{
    _box.setPosition(_position);
    _box.setSize(_size);
    _box.setFillColor(_background_color);
    _box.setOutlineColor(_primary_color);
    _box.setOutlineThickness(1.0f);

    _selectedText.setFont(_font);
    _selectedText.setString(placeholder);
    _selectedText.setOrigin({0.0f, _selectedText.getGlobalBounds().height / 2.0f});
    _selectedText.setPosition({_position.x + 10.0f, _position.y + _size.y / 2.0f});
    _selectedText.setFillColor(sf::Color(200, 200, 200));
    _selectedText.setCharacterSize(_character_size);

    _arrow.setFillColor(_primary_color);
    _arrow.setOrigin({_arrow.getRadius(), _arrow.getRadius()});
    _arrow.setPosition({position.x + _size.x - _arrow.getRadius() * 4.0f, position.y + _size.y / 2.0f});
    _arrow.rotate(180.0f);

    _texture_frame.create(_dropdown_size.x, _dropdown_size.y);
    _frame.setTexture(_texture_frame.getTexture());
    _frame.setPosition({_position.x, _position.y + _size.y});
}

void TextDropdown::addElement(sf::String const &text)
{
    _elements.emplace_back(_font, text, _size, _character_size);
    _elements.back().setPosition({0.0f, _size.y * (_elements.size() - 1)});
}

bool TextDropdown::changed()
{
    if (_changed) {
        _changed = false;
        return true;
    }
    return false;
}

sf::String TextDropdown::getValue() const
{
    return _selectedText.getString();
}

void TextDropdown::setValue(sf::String const &text)
{
    _selectedText.setString(text);
}

void TextDropdown::update(sf::RenderWindow const &window, float const elapsed_time)
{
    sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (_box.getGlobalBounds().contains(mouse_position) || (_unwrapped && _frame.getGlobalBounds().contains(mouse_position))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _state = State::CLICKED;
        } else if (_state == State::CLICKED) {
            _state = State::RELEASED;
        } else {
            _state = State::IDLE;
        }
    } else if (_unwrapped && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        _unwrapped = false;
        _state = State::IDLE;
    } else {
        _state = State::IDLE;
    }
    _arrow_clicked.update(_arrow, elapsed_time, _unwrapped, {0.0f, 0.0f}, 180.0f);
    if (_unwrapped) {
        _texture_frame.clear(_background_color);
        for (std::vector<TextDropdownElement>::iterator it = _elements.begin(); it != _elements.end(); ++it) {
            if (it->update({mouse_position.x - _position.x, mouse_position.y - _position.y - _size.y}) && _state == State::RELEASED && _selectedText.getString() != it->getValue()) {
                _selectedText.setString(it->getValue());
                _changed = true;
            }
            _texture_frame.draw(*it);
        }
        _texture_frame.display();
    }
    if (_state == State::RELEASED)
        _unwrapped = !_unwrapped;
}

void TextDropdown::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_box, states);
    target.draw(_selectedText, states);
    target.draw(_arrow, states);
    if (_unwrapped) {
        target.draw(_frame, states);
    }
}