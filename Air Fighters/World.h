#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

#include "ResourceIdentifiers.h"
#include "ResourceManager.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Aircraft.h"
#include "CommandQueue.h"

//Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);

	/**
		Called every frame to update the state of the game.
	*/
	void update(sf::Time deltaTime);

	/**
		Draws all the visible entities and scene nodes on the screen.
	*/
	void draw();

	/**
		Returns a mutable reference to the command queue
		used by the entities in the game.
	*/
	CommandQueue& getCommandQueue();

private:
	/**
		Loads all the texture files required by the entities in the game.
	*/
	void loadTextures();

	/**
		Builds the game world.
		1- Initializes the scene layers.
		2- Set up background texture
		3- Set up the airplanes (Player and escorts)
	*/
	void buildScene();

private:
	enum class Layer { Background, Air, LayerCount };

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureManager mTextures;

	SceneNode mSceneGraph;
	std::vector<SceneNode*> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	CommandQueue mCommandQueue;
};
