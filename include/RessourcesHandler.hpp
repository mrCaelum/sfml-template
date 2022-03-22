#pragma once

#include <map>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class RessourcesHandler
{
private:
	std::map<sf::String, sf::Texture> _textures;
	std::map<sf::String, sf::Font> _fonts;
	std::map<sf::String, sf::SoundBuffer> _sounds;

public:
	RessourcesHandler();
	~RessourcesHandler() = default;

	void setTexture(sf::String const &filename, sf::String const &alias = "");
	void setFont(sf::String const &filename, sf::String const &alias = "");
	void setSound(sf::String const &filename, sf::String const &alias = "");

	sf::Texture &getTexture(sf::String const &name);
	sf::Font &getFont(sf::String const &name);
	sf::SoundBuffer &getSound(sf::String const &name);
};