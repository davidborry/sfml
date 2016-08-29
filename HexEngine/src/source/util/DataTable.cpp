#include "../../headers/util/DataTable.hpp"
#include "../../headers/entities/Aircraft.hpp"
#include "../../headers/entities/Projectile.hpp"
#include "../../headers/entities/Pickup.hpp"

Direction::Direction(float angle, float distance) : angle(angle), distance(distance)
{

}

std::vector<AircraftData> initializeAircraftData(){
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::EAGLE].hitpoints = 100;
	data[Aircraft::EAGLE].speed = 200.f;
	data[Aircraft::EAGLE].texture = Resources::Textures::Entities;
	data[Aircraft::EAGLE].textureRect = sf::IntRect(0, 0, 48, 64);

	data[Aircraft::RAPTOR].hitpoints = 20;
	data[Aircraft::RAPTOR].speed = 80;
	data[Aircraft::RAPTOR].texture = Resources::Textures::Entities;
	data[Aircraft::RAPTOR].textureRect = sf::IntRect(144, 0, 84, 64);

	data[Aircraft::RAPTOR].directions.push_back(Direction(+45, 80));
	data[Aircraft::RAPTOR].directions.push_back(Direction(-45, 160));
	data[Aircraft::RAPTOR].directions.push_back(Direction(+45, 80));

	data[Aircraft::AVENGER].hitpoints = 40;
	data[Aircraft::AVENGER].speed = 50.f;
	data[Aircraft::AVENGER].texture = Resources::Textures::Entities;

	data[Aircraft::AVENGER].directions.push_back(Direction(+45, 50));
	data[Aircraft::AVENGER].directions.push_back(Direction(0, 50));
	data[Aircraft::AVENGER].directions.push_back(Direction(-45, 100));
	data[Aircraft::AVENGER].directions.push_back(Direction(0, 50));
	data[Aircraft::AVENGER].directions.push_back(Direction(+45, 50));

	data[Aircraft::AVENGER].textureRect = sf::IntRect(228, 0, 60, 59);

	return data;
}

std::vector<ProjectileData> initializeProjectileData(){
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Resources::Textures::Entities;
	data[Projectile::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Resources::Textures::Entities;
	data[Projectile::EnemyBullet].textureRect = sf::IntRect(175, 64, 3, 14);


	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Resources::Textures::Entities;
	data[Projectile::Missile].textureRect = sf::IntRect(160, 64, 15, 32);

	return data;
}

std::vector<PickupData> initializePickUpData(){
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].action = [](Aircraft& a) {a.repair(25); };
	data[Pickup::HealthRefill].texture = Resources::Textures::Entities;
	data[Pickup::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);

	data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, std::placeholders::_1);
	data[Pickup::FireRate].texture = Resources::Textures::Entities;
	data[Pickup::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);

	data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseFireSpread, std::placeholders::_1);
	data[Pickup::FireSpread].texture = Resources::Textures::Entities;
	data[Pickup::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);

	data[Pickup::MissileRefill].action = std::bind(&Aircraft::CollectMissiles, std::placeholders::_1,3);
	data[Pickup::MissileRefill].texture = Resources::Textures::Entities;
	data[Pickup::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);

	return data;
}