#include "../../headers/entities/Entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity){
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy){
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const{
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt){
		move(mVelocity*dt.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity){
	mVelocity += velocity;
}

void Entity::damage(int points){
	mHitPoints -= points;
}

void Entity::repair(int points){
	mHitPoints += points;
}

void Entity::destroy(){
	mHitPoints = 0;
}

int Entity::getHitPoints() const{
	return mHitPoints;
}