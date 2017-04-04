#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "ConcurrentTask.h"

class LoadingState : public State
{
public:
	LoadingState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time deltaTime);
	virtual bool handleEvent(const sf::Event& gameEvent);
	void setCompletion(float percent);

private:
	sf::Text mLoadingText;
	sf::RectangleShape mProgressBarBackground;
	sf::RectangleShape mProgressBar;

	ConcurrentTask mLoadingTask;
};

