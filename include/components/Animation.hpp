#pragma once

#include <SFML/Graphics/Transformable.hpp>

/**
 * @brief Animation object. Targets a sf::Tranformable object.
 */
struct Animation
{
	/**
	 * @brief The animation type. Defines the animation movement.
	 */
	enum Type {
		NONE,
		ZOOM_IN,
		ZOOM_OUT,
		TOP_TO_BOTTOM_SLIDE,
		BOTTOM_TO_TOP_SLIDE,
		LEFT_TO_RIGHT_SLIDE,
		RIGHT_TO_LEFT_SLIDE,
		POSITIVE_ROTATION,
		NEGATIVE_ROTATION
	};

	Type const type;
	float const duration;
	float const intensity;
	unsigned int const iteration;
	unsigned int state;
	float time;

	/**
	 * @brief Construct a new Animation object
	 * 
	 * @param type The animation type.
	 * @param duration The animation duration, in seconds.
	 * @param intensity The animation intensity that is a screen distance in slide animations, a coefficient in scale animations and an angle in rotation animations.
	 * @param iteration The number of steps during the animation.
	 */
	Animation(Type const type = Type::NONE, float const duration = 0.1f, float const intensity = 1.2f, unsigned int const iteration = 100U);

	/**
	 * @brief Construct a new Animation object
	 * 
	 * @param other The Animation object to copy.
	 */
	Animation(Animation const &other);

	/**
	 * @brief Destroy the Animation object
	 */
	~Animation() = default;

	/**
	 * @brief Update the targeted object based on the elapsed time.
	 * 
	 * @param transform The object to update.
	 * @param elapsed_time The elasped time since the last updated.
	 * @param anim Updates the animation state if true.
	 * @param position The target transformable position. Used to apply the correct position on the screen.
	 * @param rotation A rotation offset used in rotation animations.
	 */
	void update(sf::Transformable &transform, float const elapsed_time, bool anim = false, sf::Vector2f const &position = {0.0f, 0.0f}, float rotation = 0.0f);
};