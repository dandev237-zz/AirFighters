#include "Application.h"

Application::Application()
	: mWindow(sf::VideoMode(640, 480), "States", sf::Style::Close),
	mTextures(), mFonts(), mPlayer(),
	mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::ID::Main, "Assets/Sansation.ttf");
	mTextures.load(Textures::ID::TitleScreen, "Assets/Textures/TitleScreen.png");

	registerStates();

	//Game begins with the title screen
	mStateStack.pushState(States::ID::Title);
}

void Application::processInput()
{
	sf::Event gameEvent;
	while (mWindow.pollEvent(gameEvent))
	{
		mStateStack.handleEvent(gameEvent);

		if (gameEvent.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Application::update(sf::Time deltaTime)
{
	mStateStack.update(deltaTime);
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::ID::Title);
	mStateStack.registerState<MenuState>(States::ID::Menu);
	mStateStack.registerState<GameState>(States::ID::Game);
	mStateStack.registerState<PauseState>(States::ID::Pause);
}