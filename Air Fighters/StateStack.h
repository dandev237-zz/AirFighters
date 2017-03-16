
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <map>
#include <functional>
#include <assert.h>

#include "State.h"
#include "StateIdentifiers.h"

class StateStack : private sf::NonCopyable
{
public:
	enum class Action {Push, Pop, Clear};

public:
	explicit StateStack(State::Context context);

	/**
		Insert a mapping of the given state and a factory function to create it
		in the mFactories map.
	*/
	template<typename T>
	void registerState(States::ID stateID);

	void update(sf::Time deltaTime);
	void draw();
	void handleEvent(const sf::Event& gameEvent);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	struct PendingChange
	{
		//...
		Action action;
		States::ID stateID;
	};

	std::vector<State::StatePtr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;

	//Factory functions to create new states on-demand
	std::map<States::ID, std::function<State::StatePtr()>> mFactories;

private:
	/**
		Returns a smart pointer to the newly created state, given a
		state ID. It does so by looking up the ID in the mFactories
		map and using the adequate factory.
	*/
	State::StatePtr createState(States::ID stateID);
	void applyPendingChanges();
};

template<typename T>
inline void StateStack::registerState(States::ID stateID)
{
	auto factoryLambda = [this]()
	{
		return State::StatePtr(new T(*this, mContext));
	};

	mFactories[stateID] = factoryLambda;
}
