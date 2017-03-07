#pragma once

#include <SFML\System\Vector2.hpp>

// TODO: Convert this system for entity handling into an ECS system!!!

class Entity
{
public:

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float x, float y);

	sf::Vector2f getVelocity() const;

private:
	sf::Vector2f mVelocity;
};

