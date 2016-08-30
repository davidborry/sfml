#ifndef DATATABLE_HPP
#define DATATABLE_HPP

#include "ResourceIdentifier.hpp"
#include <vector>
#include <functional>
#include "SFML\Graphics.hpp"

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
	sf::IntRect textureRect;
	std::vector<Direction> directions;
	bool hasRollAnimation;
};

struct ProjectileData{
	int damage;
	float speed;
	Resources::Textures::ID texture;
	sf::IntRect textureRect;
};

struct PickupData{
	std::function<void(Aircraft&)> action;
	Resources::Textures::ID texture;
	sf::IntRect textureRect;
};

struct ParticleData{
	sf::Color color;
	sf::Time timelife;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickUpData();
std::vector<ParticleData> initializeParticleData();

#endif