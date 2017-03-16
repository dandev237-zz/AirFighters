#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
{
	mWorldView = window.getDefaultView();
	mWorldBounds = sf::FloatRect(
		0.0f,						//X origin position
		0.0f,						//Y origin position
		mWorldView.getSize().x,		//Width
		2000.0f);					//Height

	mSpawnPosition = sf::Vector2f(
		mWorldView.getSize().x / 2.0f,							//X
		mWorldBounds.height - mWorldView.getSize().y / 2.0f);	//Y

	mScrollSpeed = -50.0f;			//Negative so the world scrolls upwards

	mPlayerAircraft = nullptr;

	mSceneLayers.reserve(static_cast<unsigned int>(Layer::LayerCount));

	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time deltaTime)
{
	//Background scrolling
	mWorldView.move(0.0f, mScrollSpeed * deltaTime.asSeconds());
	mPlayerAircraft->setVelocity(0.0f, 0.0f);

	//Forward all commands to the scene graph
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), deltaTime);
	}

	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//Check for diagonal movements
	if (velocity.x != 0.0f && velocity.y != 0.0f)
	{
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.0f));
	}

	mPlayerAircraft->accelerate(0.0f, mScrollSpeed);

	mSceneGraph.update(deltaTime);

	//Check if plane is visible within the view
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.0f, mWorldView.getSize());
	const float borderDistance = 40.0f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

	mPlayerAircraft->setPosition(position);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	mTextures.load(Textures::ID::Eagle, "Assets/Textures/Eagle.png");
	mTextures.load(Textures::ID::Raptor, "Assets/Textures/Raptor.png");
	mTextures.load(Textures::ID::Desert, "Assets/Textures/Desert.png");
}

void World::buildScene()
{
	unsigned int layerCount = static_cast<unsigned int>(Layer::LayerCount);

	//Initialize the scene layers
	for (std::size_t i = 0; i < layerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers.push_back(layer.get());
		mSceneGraph.attachChild(std::move(layer));
	}

	//Set background texture to repeat itself
	sf::Texture& backgroundTexture = mTextures.get(Textures::ID::Desert);
	backgroundTexture.setRepeated(true);

	//Make the background texture as big as the whole world
	sf::IntRect textureRect(mWorldBounds);
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backgroundTexture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[static_cast<int>(Layer::Background)]->attachChild(std::move(backgroundSprite));

	//Add the main plane
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.0f, mScrollSpeed);
	mSceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(leader));		//Attach the planes to the Air layer

	//Add right escort to main plane
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
	leftEscort->setPosition(-80.0f, 50.0f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	//Add left escort to main plane
	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
	rightEscort->setPosition(80.0f, 50.0f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}