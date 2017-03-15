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

//Forward declarations
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void update(sf::Time deltaTime);
	void draw();

	CommandQueue& getCommandQueue();

private:
	void loadTextures();
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
