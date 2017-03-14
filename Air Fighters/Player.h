#pragma once

#include <SFML\Window\Event.hpp>
#include <map>

#include "Command.h"

//Forward declaration
class CommandQueue;

class Player
{
public:
	enum class Action
	{
		MoveUp,
		MoveDown,
		MoveRight,
		MoveLeft,
		ActionCount
	};

	Player();

	/**
		React to SFML Events.
	*/
	void handleEvent(const sf::Event& event, CommandQueue& commands);

	/**
		React to real-time input.
	*/
	void handleRealTimeInput(CommandQueue& commands);

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

private:
	static bool isRealTimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;
};

