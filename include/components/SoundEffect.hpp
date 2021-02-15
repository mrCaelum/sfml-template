#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class SoundEffect
{
private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    bool _played;

public:
    SoundEffect(sf::String const &filename);
    ~SoundEffect() = default;

    void play();
    void reset();
};