#include "MenuState.h"

MenuState::MenuState(StateStack & stack, Context context)
	: State(stack, context),
	mOptions(),
	mOptionIndex(0)
{
	sf::Texture& texture = context.mTextures->get(Textures::ID::TitleScreen);
	sf::Font& font = context.mFonts->get(Fonts::ID::Main);

	mBackgroundSprite.setTexture(texture);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	sf::FloatRect playOptionBounds = playOption.getLocalBounds();
	playOption.setOrigin(std::floor(playOptionBounds.left + playOptionBounds.width / 2.0f), std::floor(playOptionBounds.top + playOptionBounds.height / 2.0f));
	playOption.setPosition(context.mWindow->getView().getSize() / 2.0f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	sf::FloatRect exitOptionBounds = exitOption.getLocalBounds();
	exitOption.setOrigin(std::floor(exitOptionBounds.left + exitOptionBounds.width / 2.0f), std::floor(exitOptionBounds.top + exitOptionBounds.height / 2.0f));
	exitOption.setPosition(context.mWindow->getView().getSize() / 2.0f);
	mOptions.push_back(exitOption);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().mWindow;
	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	for (const sf::Text& text : mOptions)
	{
		window.draw(text);
	}
}

bool MenuState::update(sf::Time deltaTime)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& gameEvent)
{
	if (gameEvent.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (gameEvent.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == static_cast<size_t>(OptionNames::Play))
		{
			requestStackPop();
			requestStackPush(States::ID::Game);
		}
		else if (mOptionIndex == static_cast<size_t>(OptionNames::Exit))
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}
	else if (gameEvent.key.code == sf::Keyboard::Up)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
		{
			mOptionIndex--;
		}
		else
		{
			mOptionIndex = mOptions.size() - 1;
		}

		updateOptionText();
	}
	else if (gameEvent.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
		{
			mOptionIndex++;
		}
		else
		{
			mOptionIndex = 0;
		}

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
	{
		return;
	}

	for(sf::Text& text : mOptions)
	{
		text.setColor(sf::Color::White);
	}

	mOptions[mOptionIndex].setColor(sf::Color::Red);
}
