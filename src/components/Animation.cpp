#include "components/Animation.hpp"

#define MAP(x, in_min, in_max, out_min, out_max) (((float)x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

Animation::Animation(Type const type, float const duration, float const intensity, unsigned int const iteration)
: type{type}, duration{duration}, intensity{intensity}, iteration{iteration}, state{0U}, time{0.0f} {}

Animation::Animation(Animation const &other)
: type{other.type}, duration{other.duration}, intensity{other.intensity}, iteration{other.iteration}, state{other.state}, time{other.time} {}

Animation &Animation::operator=(Animation const &other)
{
	this->type = other.type;
	this->duration = other.duration;
	this->intensity = other.intensity;
	this->iteration = other.iteration;
	this->state = other.state;
	this->time = other.time;
	return *this;
}

void Animation::update(sf::Transformable &transform, float const elapsed_time, bool anim, sf::Vector2f const &position, float rotation)
{
	this->time += elapsed_time;
	while (this->time >= (this->duration / static_cast<float>(this->iteration))) {
		this->time -= (this->duration / static_cast<float>(this->iteration));

		if (!anim) {
			if (this->state > 0)
				--this->state;
		} else {
			if (this->state <= this->iteration)
				++this->state;
		}
		switch (this->type) {
			case Animation::Type::ZOOM_IN:
				transform.setScale(sf::Vector2f{1.0f, 1.0f} * MAP(this->state, 0.0f, this->iteration, 1.0f, this->intensity));
				break;
			case Animation::Type::ZOOM_OUT:
				transform.setScale(sf::Vector2f{1.0f, 1.0f} / MAP(this->state, 0.0f, this->iteration, 1.0f, this->intensity));
				break;
			case Animation::Type::TOP_TO_BOTTOM_SLIDE:
				transform.setPosition(sf::Vector2f{position.x, MAP(this->state, 0.0f, this->iteration, position.y, position.y + this->intensity)});
				break;
			case Animation::Type::BOTTOM_TO_TOP_SLIDE:
				transform.setPosition(sf::Vector2f{position.x, MAP(this->state, 0.0f, this->iteration, position.y, position.y - this->intensity)});
				break;
			case Animation::Type::LEFT_TO_RIGHT_SLIDE:
				transform.setPosition(sf::Vector2f{MAP(this->state, 0.0f, this->iteration, position.x, position.x + this->intensity), position.y});
				break;
			case Animation::Type::RIGHT_TO_LEFT_SLIDE:
				transform.setPosition(sf::Vector2f{MAP(this->state, 0.0f, this->iteration, position.x, position.x - this->intensity), position.y});
				break;
			case Animation::Type::POSITIVE_ROTATION:
				transform.setRotation(MAP(this->state, 0.0f, this->iteration, rotation, rotation - this->intensity));
				break;
			case Animation::Type::NEGATIVE_ROTATION:
				transform.setRotation(MAP(this->state, 0.0f, this->iteration, rotation, rotation + this->intensity));
				break;
			default:
				break;
		}
	}
}