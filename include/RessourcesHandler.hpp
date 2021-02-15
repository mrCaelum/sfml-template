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

    void setTexture(sf::String const &filename);
    void setFont(sf::String const &filename);
    void setSound(sf::String const &filename);

    sf::Texture &getTexture(sf::String const &filename);
    sf::Font &getFont(sf::String const &filename);
    sf::SoundBuffer &getSound(sf::String const &filename);
};