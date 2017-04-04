#pragma once

#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "Player.h"
#include "StateStack.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();

	void run();

private:
	void processInput();
	void update(sf::Time deltaTime);
	void render();
	void registerStates();

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	TextureManager mTextures;
	FontManager mFonts;
	Player mPlayer;

	StateStack mStateStack;
};
