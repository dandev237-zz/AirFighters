#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture & texture)
{
	//TODO: Implementation
}

SpriteNode::SpriteNode(const sf::Texture & texture, const sf::IntRect & rectangle)
{
	//TODO: Implementation
}

void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
