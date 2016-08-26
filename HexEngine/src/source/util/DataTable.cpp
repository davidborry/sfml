#include "../../headers/util/DataTable.hpp"
#include "../../headers/entities/Aircraft.hpp"

std::vector<AircraftData> initializeAircraftData(){
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::EAGLE].hitpoints = 100;
	data[Aircraft::EAGLE].speed = 200.f;
	data[Aircraft::EAGLE].texture = Resources::Textures::Eagle;

	data[Aircraft::RAPTOR].hitpoints = 20;
	data[Aircraft::RAPTOR].speed = 80;
	data[Aircraft::RAPTOR].texture = Resources::Textures::Raptor;

	data[Aircraft::AVENGER].hitpoints = 40;
	data[Aircraft::AVENGER].speed = 50.f;
	data[Aircraft::AVENGER].texture = Resources::Textures::Avenger;

	return data;
}