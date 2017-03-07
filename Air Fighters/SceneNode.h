#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>

class SceneNode
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode() : mParent(nullptr) {};

	/**
		Attaches a node to this node.
	*/
	void attachChild(Ptr child);

	/**
		Detaches a node from the scene graph formed by this node.
	*/
	SceneNode::Ptr detachChild(const SceneNode& node);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

