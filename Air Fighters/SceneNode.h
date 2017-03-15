#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "Category.h"
#include "Command.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	/**
		Attaches a node to this node.
	*/
	void attachChild(Ptr child);

	/**
		Detaches a node from the scene graph formed by this node.
	*/
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time deltaTime);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	virtual unsigned int getCategory() const;
	void onCommand(const Command& command, sf::Time deltaTime);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time deltaTime);
	void updateChildren(sf::Time deltaTime);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;			//TODO: Change to weak_ptr
};
