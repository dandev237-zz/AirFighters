#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context),
	mWorld(*context.mWindow),
	mPlayer(*context.mPlayer)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time deltaTime)
{
	mWorld.update(deltaTime);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& gameEvent)
{
	//Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(gameEvent, commands);

	//If escape is pressed, trigger the pause screen
	if (gameEvent.type == sf::Event::KeyPressed && gameEvent.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(States::ID::Pause);
	}

	return true;
}
