#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.0f / 60.0f);	//60 Frames Per Second

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "Air Fighters", sf::Style::Close), mWorld(mWindow)
{
	//Enables V-Sync
	mWindow.setVerticalSyncEnabled(true);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		//clock measures the time from when it was started, so we can use it to get the delta time
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;

		//Fixed Time Steps technique application
		//The same delta time is given to the update function no matter what happens
		//Interesting reading: http://gafferongames.com/game-physics/fix-your-timestep/
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents(deltaTime);
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents(const sf::Time& deltaTime)
{
	CommandQueue& commandQueue = mWorld.getCommandQueue();
	sf::Event gameEvent;

	while (mWindow.pollEvent(gameEvent))
	{
		mPlayer.handleEvent(gameEvent, commandQueue);

		if (gameEvent.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}

	mPlayer.handleRealTimeInput(commandQueue);
}

void Game::update(sf::Time deltaTime)
{
	mWorld.update(deltaTime);
}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void Game::processInput()
{
	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event gameEvent;
	while (mWindow.pollEvent(gameEvent))
	{
		mPlayer.handleEvent(gameEvent, commands);

		if (gameEvent.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}

	mPlayer.handleRealTimeInput(commands);
}