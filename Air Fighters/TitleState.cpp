#include "TitleState.h"

//Blinking effect period
const float BlinkingPeriod = 1.0f;

TitleState::TitleState(StateStack & stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.mTextures->get(Textures::ID::TitleScreen));

	mText.setFont(context.mFonts->get(Fonts::ID::Main));
	mText.setString("Press any key to start");

	float centerMeasure = context.mWindow->getView().getSize() / 2.0f;

	mText.setOrigin(centerMeasure, centerMeasure);
	mText.setPosition(centerMeasure, centerMeasure);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().mWindow;
	window.draw(mBackgroundSprite);

	if (mShowText)
	{
		window.draw(mText);
	}
}

bool TitleState::update(sf::Time deltaTime)
{
	mTextEffectTime += deltaTime;

	if (mTextEffectTime >= sf::seconds(BlinkingPeriod))
	{
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}
	
	return true;
}

bool TitleState::handleEvent(const sf::Event& gameEvent)
{
	//Activate the next screen (Main menu)
	if (gameEvent.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::ID::Menu);
	}

	return true;
}
