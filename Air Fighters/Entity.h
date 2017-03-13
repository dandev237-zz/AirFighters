#pragma once

#include <SFML\System\Vector2.hpp>

#include "SceneNode.h"

// TODO: Convert this system for entity handling into an ECS system!!!

class Entity : public SceneNode
{
public:

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float x, float y);

	sf::Vector2f getVelocity() const;
	
	void accelerate(sf::Vector2f velocity);
	void accelerate(float x, float y);

private:
	sf::Vector2f mVelocity;

private:
	virtual void updateCurrent(sf::Time deltaTime);
};

