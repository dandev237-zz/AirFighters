#pragma once

#include "State.h"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& gameEvent);

private:
	sf::Sprite mBackgroundSprite;
	sf::Text mText;

	bool mShowText;
	sf::Time mTextEffectTime;
};

