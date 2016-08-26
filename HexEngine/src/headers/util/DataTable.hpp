#ifndef DATATABLE_HPP
#define DATATABLE_HPP

#include "ResourceIdentifier.hpp"
#include <vector>

class Aircraft;

struct AircraftData{
	int hitpoints;
	float speed;
	Resources::Textures::ID texture;
};

std::vector<AircraftData> initializeAircraftData();

#endif