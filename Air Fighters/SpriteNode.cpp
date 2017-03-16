#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
	//TODO: Implementation
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle)
	: mSprite(texture, rectangle)
{
	//TODO: Implementation
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}