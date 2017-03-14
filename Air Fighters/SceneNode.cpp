#include "SceneNode.h"

SceneNode::SceneNode()
	: mChildren(), mParent(nullptr)
{
}

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

void SceneNode::update(sf::Time deltaTime)
{
	updateCurrent(deltaTime);
	updateChildren(deltaTime);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		//Step upwards in the graph and accumulate all relative transforms until mParent is reached.
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
	return static_cast<unsigned int>(Category::Type::Scene);
}

void SceneNode::onCommand(const Command& command, sf::Time deltaTime)
{
	//Check if node is a receiver of the command
	if (command.category & getCategory())
	{
		//Execute the command by calling action() callback
		command.action(*this, deltaTime);
	}

	//Forward command to all child nodes
	for (Ptr& child : mChildren)
	{
		child->onCommand(command, deltaTime);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Combine the parent's absolute transform with the current node's relative transform
	states.transform *= getTransform();

	drawCurrent(target, states);

	for (const Ptr& child : mChildren) {
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{}

void SceneNode::updateCurrent(sf::Time deltaTime)
{}

void SceneNode::updateChildren(sf::Time deltaTime)
{
	for (Ptr& child : mChildren)
	{
		child->update(deltaTime);
	}
}