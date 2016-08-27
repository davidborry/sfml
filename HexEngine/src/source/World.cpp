#include "../headers/World.h"

World::SpawnPoint::SpawnPoint(Aircraft::Type type, float x, float y):
type(type),
x(x),
y(y)
{

}

World::World(sf::RenderWindow& window, FontHolder& fonts) : mWindow(window),
mFonts(fonts),
mWorldView(window.getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
mSpawnPosition(mWorldView.getSize().x/2, mWorldBounds.height - mWorldView.getSize().y),
mScrollSpeed(-50.f),
mPlayerAircraft(nullptr),
mEnemySpointPoints()
{
	loadTextures();
	buildScene();

	addEnemies();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures(){
	mTextures.load(Resources::Textures::Eagle, "Resources/img/plane.png");
	mTextures.load(Resources::Textures::Raptor, "Resources/img/drone.png");
	mTextures.load(Resources::Textures::Desert, "Resources/img/sand.jpg");
	mTextures.load(Resources::Textures::Avenger, "Resources/img/Avenger.png");
}

void World::buildScene(){

	//Initialize each layer
	for (std::size_t i = 0; i < LayerCount; ++i){
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	//Initialize desert sprite node
	sf::Texture& texture = mTextures.get(Resources::Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	//Initialize planes
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::EAGLE, mTextures, mFonts));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	/**std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::RAPTOR, mTextures, mFonts));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));
	

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::RAPTOR, mTextures, mFonts));
	rightEscort->setPosition(80.f,50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));**/

}

void World::draw(){
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt){
	mWorldView.move(0.f, mScrollSpeed*dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);
	
	spawnEnemies();

	//forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	if (velocity.x != 0 && velocity.y != 0)
		mPlayerAircraft->setVelocity(velocity/std::sqrt(2.f));

	mSceneGraph.update(dt);

	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

	mPlayerAircraft->setPosition(position);
}

CommandQueue& World::getCommandQueue(){
	return mCommandQueue;
}

sf::FloatRect World::getViewBounds() const {
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const {
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

void World::spawnEnemies(){
	while (!mEnemySpointPoints.empty() && mEnemySpointPoints.back().y > getViewBounds().top){

		SpawnPoint spawn = mEnemySpointPoints.back();

		std::unique_ptr<Aircraft> ennemy(new Aircraft(spawn.type, mTextures, mFonts));
		ennemy->setPosition(spawn.x, spawn.y);
		ennemy->setRotation(180.f);

		mSceneLayers[Air]->attachChild(std::move(ennemy));

		mEnemySpointPoints.pop_back();
	}
}

void World::addEnemy(Aircraft::Type type, float x, float y){
	mEnemySpointPoints.push_back(SpawnPoint(type, mSpawnPosition.x + x, mSpawnPosition.y - y));
}

void World::addEnemies(){
	addEnemy(Aircraft::RAPTOR, 0.f, 500.f);
	addEnemy(Aircraft::RAPTOR, 0.f, 1000.f);
	addEnemy(Aircraft::RAPTOR, +100.f, 1100.f);
	addEnemy(Aircraft::RAPTOR, -100.f, 1100.f);
	addEnemy(Aircraft::AVENGER, -70.f, 1400.f);
	addEnemy(Aircraft::AVENGER, -70.f, 1600.f);
	addEnemy(Aircraft::AVENGER, 70.f, 1400.f);
	addEnemy(Aircraft::AVENGER, 70.f, 1600.f);

	std::sort(mEnemySpointPoints.begin(), mEnemySpointPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs){
		return lhs.y < rhs.y;
	});

}