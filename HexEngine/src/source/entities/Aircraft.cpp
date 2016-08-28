#include "../../headers/entities/Aircraft.hpp"
#include "../../headers/util/Utility.hpp"
#include "../../headers/commands/CommandQueue.hpp"

Resources::Textures::ID toTextureID(Aircraft::Type id){
	switch (id){
	case Aircraft::Type::EAGLE:
		return Resources::Textures::Eagle;

	case Aircraft::Type::RAPTOR:
		return Resources::Textures::Raptor;

	case Aircraft::Type::AVENGER:
		return Resources::Textures::Avenger;
	}
}

namespace{
	const std::vector<AircraftData> Table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts): 
Entity(Table[type].hitpoints),
mType(type),
mSprite(textures.get(toTextureID(type))),
mDirectionIndex(0),
mTravelledDistance(0.f),
mFireCountdown(sf::Time::Zero),
mIsFiring(false),
mIsLaunchingMissile(false),
mFireRateLevel(1),
mFireCommand(),
mMissileCommand(),
mSpreadLevel(1),
mMissiles(3)


{
	mFireCommand.category = Category::SceneAirLayer;
	mFireCommand.action = 
	[this, &textures](SceneNode& node, sf::Time) {
		createBullets(node, textures);
	};

	mMissileCommand.category = Category::SceneAirLayer;
	mMissileCommand.action = 
		[this, &textures](SceneNode& node, sf::Time){
		createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
	};

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	mHitPoints = Table[mType].hitpoints;
	// printf("%i\n", Table[mType].hitpoints);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands){
	Entity::updateCurrent(dt, commands);
	mHealthDisplay->setString(toString(getHitPoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

	checkProjectileLaunch(dt, commands);
	updateMovementPattern(dt);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const{
	switch (mType){
	case EAGLE:
		return Category::PlayerAircraft;

	case RAPTOR:
		return Category::AlliedAircraft;

	default:
		return Category::EnemyAircraft;
	}
}

void Aircraft::updateMovementPattern(sf::Time dt){
	const std::vector<Direction>& directions = Table[mType].directions;
	if (!directions.empty()){
		float distanceToTravel = directions[mDirectionIndex].distance;

		if (mTravelledDistance > distanceToTravel){
			mDirectionIndex = (mDirectionIndex + 1) % directions.size();
			mTravelledDistance = 0.f;
		}

		// 0° in SFML = Right orientation.
		float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		setVelocity(vx, vy);
		mTravelledDistance += getMaxSpeed() * dt.asSeconds();
		
	}
		
}

float Aircraft::getMaxSpeed() const{
	return Table[mType].speed;
}

void Aircraft::fire(){
	mIsFiring = true;
}

void Aircraft::launchMissile(){
	if (mMissiles > 0)
		mIsLaunchingMissile = true;
}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commands){

	

	if (!isAllied())
		fire();

	if (mIsFiring && mFireCountdown <= sf::Time::Zero){
		commands.push(mFireCommand);
		mFireCountdown += sf::seconds(1.f / (mFireRateLevel + 1));
		mIsFiring = false;
	}

	else if (mFireCountdown > sf::Time::Zero)
		mFireCountdown -= dt;
	

	if (mIsLaunchingMissile){
		printf("test\n");
		commands.push(mMissileCommand);
		mIsLaunchingMissile = false;
		mMissiles--;
	}
}

void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures) const {
	//printf("Test\n");
	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;
	
	switch (mSpreadLevel){
	case 1:
		createProjectile(node, type, 0.0f, 0.5f, textures);
		break;
		
	case 2:
		createProjectile(node, type, -0.33f, 0.33f, textures);
		createProjectile(node, type, +0.33f, 0.33f, textures);
		break;

	case 3:
		createProjectile(node, type, -0.5f, 0.33f, textures);
		createProjectile(node, type, 0.0f, 0.5f, textures);
		createProjectile(node, type, +0.5f, 0.33f, textures);
		break;
	}

}

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const {
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset*mSprite.getGlobalBounds().height);
	sf::Vector2f velocity(0.f, projectile->getMaxSpeed());

	float sign = isAllied() ? -1.f : +1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);

	node.attachChild(std::move(projectile));
}

bool Aircraft::isAllied() const{
	return mType == EAGLE;
}

void Aircraft::increaseFireRate(){
	mFireRateLevel++;
}

void Aircraft::increaseFireSpread(){
	if (mSpreadLevel < 3)
		mSpreadLevel++;
}

void Aircraft::CollectMissiles(int m){
	mMissiles += m;
}