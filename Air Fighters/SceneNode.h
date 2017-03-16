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

	/**
		Updates the state of this node.
	*/
	void update(sf::Time deltaTime);

	//Getters for transform and position
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	/**
		Getter for the node category. Virtual so that each node can
		have its own implementation.
	*/
	virtual unsigned int getCategory() const;

	/**
		Callback used when the node receives a command.
	*/
	void onCommand(const Command& command, sf::Time deltaTime);

private:
	/**
		Draws the node to the game window.
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time deltaTime);

	/**
		Updates the states of this node's children.
		Used when the update() method is called.
	*/
	void updateChildren(sf::Time deltaTime);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;			//TODO: Change to weak_ptr
};
