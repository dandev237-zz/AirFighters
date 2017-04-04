#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"

class PauseState : public State
{
	public:
		PauseState(StateStack& stack, Context context);

		virtual void draw();
		virtual bool update(sf::Time deltaTime);
		virtual bool handleEvent(const sf::Event& gameEvent);
	
	private:
		sf::Sprite mBackgroundSprite;
		sf::Text mPausedText;
		sf::Text mInstructionText;
};

