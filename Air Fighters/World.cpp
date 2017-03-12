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

	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time deltaTime)
{
	//Background scrolling
	mWorldView.move(0.0f, mScrollSpeed * deltaTime.asSeconds());

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	//Player border constraint
	if (position.x <= mWorldBounds.left + 150 || position.x > mWorldBounds.left + mWorldBounds.width - 150) 
	{
		velocity.x = 0.0f;
		mPlayerAircraft->setVelocity(velocity);
	}

	mSceneGraph.update(deltaTime);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::ID::Eagle, "Assets/Textures/Eagle.png");
	mTextures.load(Textures::ID::Raptor, "Assets/Textures/Raptor.png");
	mTextures.load(Textures::ID::Desert, "Assets/Textures/Desert.png");
}

void World::buildScene()
{
	//Initialize the scene layers
	for (auto layer : mSceneLayers) {
		SceneNode::Ptr newLayer(new SceneNode());
		layer = newLayer.get();			//get() does not transfer ownership
		mSceneGraph.attachChild(std::move(newLayer));
	}

	//Set background texture to repeat itself
	sf::Texture& backgroundTexture = mTextures.get(Textures::ID::Desert);
	backgroundTexture.setRepeated(true);
	
	//Make the background texture as big as the whole world
	sf::IntRect textureRect(mWorldBounds);
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(backgroundTexture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[static_cast<int>(Layer::Background)]->attachChild(std::move(backgroundSprite));

	//Add the airplanes
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
