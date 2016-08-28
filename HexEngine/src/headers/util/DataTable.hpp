#ifndef DATATABLE_HPP
#define DATATABLE_HPP

#include "ResourceIdentifier.hpp"
#include <vector>
#include <functional>

class Aircraft;


struct Direction{
	Direction(float angle, float distance);

	float angle;
	float distance;
};

struct AircraftData{
	int hitpoints;
	float speed;
	Resources::Textures::ID texture;
	std::vector<Direction> directions;
};

struct ProjectileData{
	int damage;
	float speed;
	Resources::Textures::ID texture;
};

struct PickupData{
	std::function<void(Aircraft&)> action;
	Resources::Textures::ID texture;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickUpData();

#endif