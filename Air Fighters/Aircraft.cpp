#include "Aircraft.h"

Textures::ID toTextureID(Aircraft::Type type)
{
	Textures::ID texture;

	switch (type)
	{
	case Aircraft::Type::Eagle:
		texture = Textures::ID::Eagle;
		break;
	case Aircraft::Type::Raptor:
		texture = Textures::ID::Raptor;
		break;
	}

	return texture;
}

Aircraft::Aircraft(Type type, const TextureManager& textures)
	: mType(type), mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Type::Eagle:
		return static_cast<unsigned int>(Category::Type::PlayerAircraft);
		break;

	default:
		return static_cast<unsigned int>(Category::Type::EnemyAircraft);
		break;
	}
}