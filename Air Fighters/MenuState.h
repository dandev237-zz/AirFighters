#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"

class MenuState : public State
{
	public:
		MenuState(StateStack& stack, Context context);

		virtual void draw();
		virtual bool update(sf::Time deltaTime);
		virtual bool handleEvent(const sf::Event& gameEvent);
		void updateOptionText();

	private:
		enum class OptionNames
		{
			Play,
			Exit
		};

	private:
		sf::Sprite mBackgroundSprite;
		std::vector<sf::Text> mOptions;
		std::size_t mOptionIndex;
};

