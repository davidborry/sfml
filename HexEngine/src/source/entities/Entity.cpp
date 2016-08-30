#include "../../headers/entities/Entity.hpp"

Entity::Entity(int hitPoints) : 
mHitPoints(hitPoints)
{
}

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

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands){
		move(mVelocity*dt.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity){
	mVelocity += velocity;
}

void Entity::damage(int points){
	mHitPoints -= points;
	if(isDestroyed())
		destroy();
}

void Entity::repair(int points){
	mHitPoints += points;
}

void Entity::destroy(){
//	printf("Dead\n");
	mHitPoints = 0;
}

int Entity::getHitPoints() const{
	return mHitPoints;
}

bool Entity::isDestroyed() const{
	return mHitPoints <= 0;
}

void Entity::remove(){
	destroy();
}