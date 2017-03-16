#include "StateStack.h"

State::StatePtr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	//Invoke the factory method
	return found->second();
}
