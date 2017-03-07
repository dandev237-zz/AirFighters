#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode() : mParent(nullptr) {};
	virtual ~SceneNode() {};

	/**
		Attaches a node to this node.
	*/
	void attachChild(Ptr child);

	/**
		Detaches a node from the scene graph formed by this node.
	*/
	Ptr detachChild(const SceneNode& node);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

