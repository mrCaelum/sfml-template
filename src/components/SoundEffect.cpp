#include "SoundEffect.hpp"

SoundEffect::SoundEffect(sf::SoundBuffer const &buffer)
: _sound{}, _played{false}
{
    _sound.setBuffer(buffer);
}

void SoundEffect::play()
{
    if (!_played) {
        _sound.play();
        _played = true;
    }
}

void SoundEffect::reset()
{
    _played = false;
}