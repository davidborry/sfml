#include "../headers/World.h"

World::World(sf::RenderWindow& window) : mWindow(window),
mWorldView(window.getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
mSpawnPosition(mWorldView.getSize().x/2, mWorldBounds.height - mWorldView.getSize().y),
mScrollSpeed(-50.f),
mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures(){
	mTextures.load(Textures::Eagle, "Resources/img/plane.png");
	mTextures.load(Textures::Raptor, "Resources/img/drone.png");
	mTextures.load(Textures::Desert, "Resources/img/sand.jpg");
}

void World::buildScene(){

	//Initialize each layer
	for (std::size_t i = 0; i < LayerCount; ++i){
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	//Initialize desert sprite node
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	//Initialize planes
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::EAGLE, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::RAPTOR, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));
	

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::RAPTOR, mTextures));
	rightEscort->setPosition(80.f,50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));

}

void World::draw(){
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt){
	mWorldView.move(0.f, mScrollSpeed*dt.asSeconds());

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150){
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	//forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	mSceneGraph.update(dt);
}

CommandQueue& World::getCommandQueue(){
	return mCommandQueue;
}
