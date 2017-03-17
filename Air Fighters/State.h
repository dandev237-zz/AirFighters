#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

#include "StateStack.h"
#include "Player.h"
#include "ResourceIdentifiers.h"

class State
{
public:
	typedef std::unique_ptr<State> StatePtr;

	//Context struct to reuse assets for every state.
	struct Context
	{
		Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, Player& player);

		sf::RenderWindow* mWindow;
		TextureManager* mTextures;
		FontManager* mFonts;
		Player* mPlayer;
	};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time deltaTime) = 0;
	virtual bool handleEvent(const sf::Event& gameEvent) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack*	mStack;
	Context mContext;
};
