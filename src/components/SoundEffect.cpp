#include "SoundEffect.hpp"

SoundEffect::SoundEffect(sf::String const &filename)
: _buffer{}, _sound{}, _played{false}
{
    _buffer.loadFromFile(filename);
    _sound.setBuffer(_buffer);
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