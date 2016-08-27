#include "../../headers/entities/Aircraft.hpp"
#include "../../headers/util/Utility.hpp"

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

Aircraft::Aircraft(Type type): 
mType(type),
mDirectionIndex(0),
mTravelledDistance(0.f)
{
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts): mType(type), mSprite(textures.get(toTextureID(type))) {
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	mHitPoints = Table[mType].hitpoints;
	// printf("%i\n", Table[mType].hitpoints);
}

void Aircraft::updateCurrent(sf::Time dt){
	Entity::updateCurrent(dt);
	mHealthDisplay->setString(toString(getHitPoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

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