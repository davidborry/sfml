#include "../../headers/util/DataTable.hpp"
#include "../../headers/entities/Aircraft.hpp"
#include "../../headers/entities/Projectile.hpp"

Direction::Direction(float angle, float distance) : angle(angle), distance(distance)
{

}

std::vector<AircraftData> initializeAircraftData(){
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::EAGLE].hitpoints = 100;
	data[Aircraft::EAGLE].speed = 200.f;
	data[Aircraft::EAGLE].texture = Resources::Textures::Eagle;

	data[Aircraft::RAPTOR].hitpoints = 20;
	data[Aircraft::RAPTOR].speed = 80;
	data[Aircraft::RAPTOR].texture = Resources::Textures::Raptor;

	data[Aircraft::RAPTOR].directions.push_back(Direction(+45, 80));
	data[Aircraft::RAPTOR].directions.push_back(Direction(-45, 160));
	data[Aircraft::RAPTOR].directions.push_back(Direction(+45, 80));


	data[Aircraft::AVENGER].hitpoints = 40;
	data[Aircraft::AVENGER].speed = 50.f;
	data[Aircraft::AVENGER].texture = Resources::Textures::Avenger;

	data[Aircraft::AVENGER].directions.push_back(Direction(+45, 50));
	data[Aircraft::AVENGER].directions.push_back(Direction(0, 50));
	data[Aircraft::AVENGER].directions.push_back(Direction(-45, 100));
	data[Aircraft::AVENGER].directions.push_back(Direction(0, 50));
	data[Aircraft::AVENGER].directions.push_back(Direction(+45, 50));


	return data;
}

std::vector<ProjectileData> initializeProjectileData(){
	std::vector<ProjectileData> data(Projectile::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Resources::Textures::Bullet;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Resources::Textures::Bullet;

	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Resources::Textures::Missile;

	return data;
}