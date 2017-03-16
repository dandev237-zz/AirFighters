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
		Initializes bindings and actions when the game begins.
	*/
	void InitializeBindings();

	/**
		React to SFML Events.
	*/
	void handleEvent(const sf::Event& event, CommandQueue& commands);

	/**
		React to real-time input.
	*/
	void handleRealTimeInput(CommandQueue& commands);

	/**
		Binds a given action to a given key.
		Any other bindings to the same action are deleted beforehand.
	*/
	void assignKey(Action action, sf::Keyboard::Key key);

	/**
		Gets the key assigned to a given action.
	*/
	sf::Keyboard::Key getAssignedKey(Action action) const;

private:
	/**
		Checks whether or not a given action is a realtime action
		(It can be handled at runtime)
	*/
	static bool isRealTimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;
};
