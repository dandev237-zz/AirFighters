#pragma once

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable
{
public:
	Game();
	~Game();

	/**
		Calls the game loop.
	*/
	void run();

private:
	/**
		Handles game events.
	*/
	void processEvents();

	/**
		Updates the game logic.
	*/
	void update(sf::Time deltaTime);

	/**
		Renders the game to the screen.
		1- Clear the game window.
		2- Draw all the objects of the current frame.
		3- Display drawn objects on the screen.
	*/
	void render();

	/**
		Handles game events related to user input.
	*/
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;

	bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
};

