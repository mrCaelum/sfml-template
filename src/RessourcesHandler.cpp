#include "RessourcesHandler.hpp"

RessourcesHandler::RessourcesHandler()
: _textures{}, _fonts{}, _sounds{} {}

void RessourcesHandler::setTexture(sf::String const &filename, sf::String const &alias)
{
	_textures[alias == "" ? filename : alias] = sf::Texture{};
	_textures[alias == "" ? filename : alias].loadFromFile(filename);
}

void RessourcesHandler::setFont(sf::String const &filename, sf::String const &alias)
{
	_fonts[alias == "" ? filename : alias] = sf::Font{};
	_fonts[alias == "" ? filename : alias].loadFromFile(filename);
}

void RessourcesHandler::setSound(sf::String const &filename, sf::String const &alias)
{
	_sounds[alias == "" ? filename : alias] = sf::SoundBuffer{};
	_sounds[alias == "" ? filename : alias].loadFromFile(filename);
}

sf::Texture &RessourcesHandler::getTexture(sf::String const &name)
{
	return _textures[name];
}

sf::Font &RessourcesHandler::getFont(sf::String const &name)
{
	return _fonts[name];
}

sf::SoundBuffer &RessourcesHandler::getSound(sf::String const &name)
{
	return _sounds[name];
}