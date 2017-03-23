#pragma once

#include "State.h"
#include "StateStack.h"
#include "World.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& gameEvent);

private:
	World mWorld;
	Player mPlayer;
};
