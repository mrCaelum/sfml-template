#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class SoundEffect
{
private:
    sf::Sound _sound;
    bool _played;

public:
    SoundEffect(sf::SoundBuffer const &buffer);
    ~SoundEffect() = default;

    void play();
    void reset();
};