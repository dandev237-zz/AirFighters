#include "Player.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Aircraft.h"

struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	InitializeBindings();

	for (auto& pair : mActionBinding)
	{
		pair.second.category = static_cast<unsigned int>(Category::Type::PlayerAircraft);
	}
}

void Player::InitializeBindings()
{
	const float playerSpeed = 200.f;

	//Key bindings
	mKeyBinding[sf::Keyboard::W] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::S] = Action::MoveDown;
	mKeyBinding[sf::Keyboard::A] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::D] = Action::MoveRight;

	//Action bindings
	mActionBinding[Action::MoveUp].action = Command::derivedAction<Aircraft>(AircraftMover(0.0f, -playerSpeed));
	mActionBinding[Action::MoveDown].action = Command::derivedAction<Aircraft>(AircraftMover(0.0f, +playerSpeed));
	mActionBinding[Action::MoveLeft].action = Command::derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.0f));
	mActionBinding[Action::MoveRight].action = Command::derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.0f));
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		//If pressed key is binded, trigger command
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealTimeAction(found->second))
		{
			commands.push(mActionBinding[found->second]);
		}
	}
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first)
			&& isRealTimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto binding : mKeyBinding)
	{
		if (binding.second == action)
		{
			mKeyBinding.erase(binding.first);
		}
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto binding : mKeyBinding)
	{
		if (binding.second == action)
		{
			return binding.first;
		}
	}

	return sf::Keyboard::Unknown;
}

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
	case Action::MoveUp:
	case Action::MoveDown:
	case Action::MoveLeft:
	case Action::MoveRight:
		return true;

	default:
		return false;
	}
}