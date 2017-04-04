#include "PauseState.h"

PauseState::PauseState(StateStack & stack, Context context)
	: State(stack, context),
	mBackgroundSprite(),
	mPausedText(),
	mInstructionText()
{
	sf::Font& font = context.mFonts->get(Fonts::ID::Main);
	sf::Vector2f viewSize = context.mWindow->getView().getSize();

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	sf::FloatRect pausedTextBounds = mPausedText.getLocalBounds();
	mPausedText.setOrigin(std::floor(pausedTextBounds.left + pausedTextBounds.width / 2.0f), std::floor(pausedTextBounds.top + pausedTextBounds.height / 2.0f));
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");
	sf::FloatRect instructionTextBounds = mInstructionText.getLocalBounds();
	mInstructionText.setOrigin(std::floor(instructionTextBounds.left + instructionTextBounds.width / 2.0f), std::floor(instructionTextBounds.top + instructionTextBounds.height / 2.0f));
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().mWindow;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time deltaTime)
{
	return false;	//Trick to "pause" the game
}

bool PauseState::handleEvent(const sf::Event& gameEvent)
{
	if (gameEvent.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (gameEvent.key.code == sf::Keyboard::Escape)
	{
		// Escape pressed, remove itself to return to the game
		requestStackPop();
	}

	if (gameEvent.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();	//To make sure we clear all states before displaying the main menu
		requestStackPush(States::ID::Menu);
	}

	return false;
}


