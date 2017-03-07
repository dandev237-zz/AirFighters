#include "SceneNode.h"

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;

	//The parent is now the owner of the child
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	//Lambda expression defined to find the address of the node to detach
	auto predicate = [&](Ptr& p) -> bool { return p.get() == &node; };

	auto found = std::find_if(mChildren.begin(), mChildren.end(), predicate);
	assert(found != mChildren.end());

	//Detached node isolation
	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	
	return result;
}
