#include "RessourcesHandler.hpp"

RessourcesHandler::RessourcesHandler()
: _textures{}, _fonts{}, _sounds{} {}

void RessourcesHandler::setTexture(sf::String const &filename)
{
    _textures[filename] = sf::Texture{};
    _textures[filename].loadFromFile(filename);
}

void RessourcesHandler::setFont(sf::String const &filename)
{
    _fonts[filename] = sf::Font{};
    _fonts[filename].loadFromFile(filename);
}

void RessourcesHandler::setSound(sf::String const &filename)
{
    _sounds[filename] = sf::SoundBuffer{};
    _sounds[filename].loadFromFile(filename);
}

sf::Texture &RessourcesHandler::getTexture(sf::String const &filename)
{
    return _textures[filename];
}

sf::Font &RessourcesHandler::getFont(sf::String const &filename)
{
    return _fonts[filename];
}

sf::SoundBuffer &RessourcesHandler::getSound(sf::String const &filename)
{
    return _sounds[filename];
}