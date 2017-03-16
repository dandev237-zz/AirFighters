#pragma once

#include <memory>

#include "StateStack.h"

class State
{
public:
	typedef std::unique_ptr<State> StatePtr;
	struct Context
	{

	};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time deltaTime) = 0;
	virtual bool handleEvent(const sf::Event& gameEvent) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack*	mStack;
	Context mContext;
};

