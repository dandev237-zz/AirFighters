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
		timeSinceLastUpdate += clock.restart();

		//Fixed Time Steps technique application
		//The same delta time is given to the update function no matter what happens
		//Interesting reading: http://gafferongames.com/game-physics/fix-your-timestep/
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event gameEvent;
	while (mWindow.pollEvent(gameEvent))
	{
		switch (gameEvent.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(gameEvent.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(gameEvent.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
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

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
	{
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::S)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::A)
	{
		mIsMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		mIsMovingRight = isPressed;
	}
}