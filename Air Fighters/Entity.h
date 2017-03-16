#pragma once

#include <SFML\System\Vector2.hpp>

#include "SceneNode.h"

// TODO: Convert this system for entity handling into an ECS system!!!

class Entity : public SceneNode
{
public:

	/**
		Sets the entity's velocity to a given value.
	*/
	void setVelocity(sf::Vector2f velocity);

	/**
		Sets the entity's velocity to a given value
		in float format.
	*/
	void setVelocity(float x, float y);

	/**
		Getter for the entity's velocity.
	*/
	sf::Vector2f getVelocity() const;

	/**
		Applies an impulse to the entity
		quantified by a float vector.
	*/
	void accelerate(sf::Vector2f velocity);

	/**
		Applies an impulse to the entity
		quantified by the components of a float vector.
	*/
	void accelerate(float x, float y);

private:
	sf::Vector2f mVelocity;

private:
	/**
		Updates the state of this entity.
	*/
	virtual void updateCurrent(sf::Time deltaTime);
};
