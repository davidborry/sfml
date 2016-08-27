#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"

class Projectile : public Entity{

public:
	enum Type{
		AlliedBullet,
		EnemyBullet,
		Missile,
		TypeCount
	};

private:
	Type mType;
	sf::Sprite mSprite;
	sf::Vector2f mTargetDirection;
};

#endif