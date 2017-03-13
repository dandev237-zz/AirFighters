#include "Player.h"

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
	mKeyBinding[sf::Keyboard::Up] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::Down] = Action::MoveDown;
	mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;

	const float playerSpeed = 200.f;

	//Initial action bindings
	mActionBinding[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
	mActionBinding[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));

	for (auto& pair : mActionBinding) 
	{
		pair.second.category = static_cast<unsigned int>(Category::Type::PlayerAircraft);
	}
}

void Player::handleEvent(const sf::Event & event, CommandQueue & commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
		Command output;
		output.category = static_cast<unsigned int>(Category::Type::PlayerAircraft);
		output.action = [](SceneNode& node, sf::Time)
		{
			printf("%f, %f\n", node.getPosition().x, node.getPosition().y);
		};

		commands.push(output);
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
