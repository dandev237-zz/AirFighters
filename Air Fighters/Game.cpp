#include "Game.h"

const float Game::PlayerSpeed = 100.0f;
const sf::Time Game::TimePerFrame = sf::seconds(1.0f / 60.0f);	//60 Frames Per Second

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "Air Fighters"), mTexture(), mPlayer(),
	mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false), mIsMovingUp(false)
{
	if (!mTexture.loadFromFile("Assets/Textures/Eagle.png"))
	{
		// TODO: Handle loading error
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.0f, 100.0f);

	//Enables V-Sync
	mWindow.setVerticalSyncEnabled(true);
}


Game::~Game()
{}

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
	sf::Vector2f movement(0.0f, 0.0f);

	if (mIsMovingUp)
	{
		movement.y -= PlayerSpeed;
	}
	if (mIsMovingDown)
	{
		movement.y += PlayerSpeed;
	}
	if (mIsMovingLeft)
	{
		movement.x -= PlayerSpeed;
	}
	if (mIsMovingRight)
	{
		movement.x += PlayerSpeed;
	}

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
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