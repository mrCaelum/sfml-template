#pragma once

#include <SFML/System/String.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

/**
 * @brief A sound effect component.
 */
class SoundEffect
{
private:
	sf::Sound _sound;
	bool _played;

public:
	/**
	 * @brief Construct a new Sound Effect object
	 * 
	 * @param buffer The soundbuffer object from which the object will be created.
	 */
	SoundEffect(sf::SoundBuffer const &buffer);

	/**
	 * @brief Destroy the Sound Effect object
	 */
	~SoundEffect() = default;

	/**
	 * @brief Plays the sound.
	 */
	void play();

	/**
	 * @brief Resets the played state.
	 */
	void reset();
};