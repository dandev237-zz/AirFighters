#include "StateStack.h"

State::StatePtr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	//Invoke the factory method
	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Action::Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Action::Pop:
			mStack.pop_back();
			break;

		case Action::Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}

void StateStack::update(sf::Time deltaTime)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
	{
		if (!(*it)->update(deltaTime))
		{
			break;	//State pointed by it doesn't want to let input flow to other states
		}
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::StatePtr& state : mStack)
	{
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event & gameEvent)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
	{
		if (!(*it)->handleEvent(gameEvent))
		{
			break;	//State pointed by it doesn't want to let input flow to other states
		}
	}

	applyPendingChanges();
}