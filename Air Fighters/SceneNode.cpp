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

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Combine the parent's absolute transform with the current node's relative transform
	states.transform *= getTransform();

	drawCurrent(target, states);

	for (const Ptr& child: mChildren) {
		child->draw(target, states);
	}
}
