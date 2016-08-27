#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML\Graphics.hpp>
#include "../scene/SceneNode.hpp"
#include "../util//ResourceHolder.hpp"
#include "../util/ResourceIdentifier.hpp"

class Entity : public SceneNode{
public:
	explicit Entity(int hitPoints);

	void setVelocity(sf::Vector2f vector);
	void setVelocity(float vx, float vy);
	
	sf::Vector2f getVelocity() const;
	void accelerate(sf::Vector2f velocity);

	void repair(int points);
	void damage(int points);
	void destroy();

	int getHitPoints() const;
	bool isDestroyed() const;


protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

protected:
	sf::Vector2f mVelocity;
	int mHitPoints;
};

#endif