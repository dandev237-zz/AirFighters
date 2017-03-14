#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float x, float y)
{
	mVelocity.x = x;
	mVelocity.y = y;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::accelerate(float x, float y)
{
	mVelocity.x += x;
	mVelocity.y += y;
}

void Entity::updateCurrent(sf::Time deltaTime)
{
	move(mVelocity * deltaTime.asSeconds());
}