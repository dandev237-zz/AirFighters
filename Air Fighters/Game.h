#pragma once

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Player.h"

class Game : private sf::NonCopyable
{
public:
	Game();

	/**
		Calls the game loop.
	*/
	void run();

private:
	/**
		Handles game events.
	*/
	void processEvents(const sf::Time& deltaTime);

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
	void processInput();

private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	World mWorld;
	Player mPlayer;
};