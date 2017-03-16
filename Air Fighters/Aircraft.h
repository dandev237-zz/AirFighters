#pragma once

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

class Aircraft : public Entity
{
public:
	enum class Type { Eagle, Raptor };

public:
	Aircraft(Type type, const TextureManager& textures);

	/**
		Draws the airplane on the screen.
		states contains the states used for drawing
		(blend mode, transform, texture and shader).
	*/
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
		Returns the category of the airplane converted
		to an useful format (unsigned int)
	*/
	virtual unsigned int getCategory() const;

private:
	Type mType;
	sf::Sprite mSprite;
};
