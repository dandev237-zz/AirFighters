#pragma once

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "ResourceManager.h"

class Aircraft : public Entity
{
public:
	enum class Type {Eagle, Raptor};

public:
	Aircraft(Type type, const TextureManager& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getCategory() const;

private:
	Type mType;
	sf::Sprite mSprite;
};

