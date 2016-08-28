#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "../util/DataTable.hpp"
#include "../scene/TextNode.hpp"
#include "../commands/Command.hpp"
#include "Projectile.hpp"

class Aircraft : public Entity{
public:
	enum Type{
		EAGLE,
		RAPTOR,
		AVENGER,
		TypeCount,
	};

public:
	
	Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getCategory() const;
	float getMaxSpeed() const;

	virtual sf::FloatRect getBoundingRect() const;

	void fire();
	void launchMissile();
	void increaseFireRate();
	void CollectMissiles(int m);
	void increaseFireSpread();

	bool isAllied() const;
	virtual bool isMarkedForRemoval() const;
	virtual void destroy();

private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	void updateMovementPattern(sf::Time dt);
	void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
	void createBullets(SceneNode& node, const TextureHolder& textures) const;
	void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;

private:
	Type mType;
	sf::Sprite mSprite;

	TextNode* mHealthDisplay;
	TextNode* mMissilesDisplay;

	int mDirectionIndex;
	float mTravelledDistance;

	bool mIsFiring;
	bool mIsLaunchingMissile;
	sf::Time mFireCountdown;
	int mFireRateLevel;
	int mSpreadLevel;
	int mMissiles;

	Command mFireCommand;
	Command mMissileCommand;

	bool mIsMarkedForRemoval;
};

#endif