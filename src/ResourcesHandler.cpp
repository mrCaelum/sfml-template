#include "ResourcesHandler.hpp"

ResourcesHandler::ResourcesHandler()
: _textures{}, _fonts{}, _sounds{} {}

void ResourcesHandler::setTexture(sf::String const &filename, sf::String const &alias)
{
	_textures[alias == "" ? filename : alias] = sf::Texture{};
	_textures[alias == "" ? filename : alias].loadFromFile(filename);
}

void ResourcesHandler::setFont(sf::String const &filename, sf::String const &alias)
{
	_fonts[alias == "" ? filename : alias] = sf::Font{};
	_fonts[alias == "" ? filename : alias].loadFromFile(filename);
}

void ResourcesHandler::setSound(sf::String const &filename, sf::String const &alias)
{
	_sounds[alias == "" ? filename : alias] = sf::SoundBuffer{};
	_sounds[alias == "" ? filename : alias].loadFromFile(filename);
}

sf::Texture &ResourcesHandler::getTexture(sf::String const &name)
{
	return _textures[name];
}

sf::Font &ResourcesHandler::getFont(sf::String const &name)
{
	return _fonts[name];
}

sf::SoundBuffer &ResourcesHandler::getSound(sf::String const &name)
{
	return _sounds[name];
}