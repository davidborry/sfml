#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML\Graphics.hpp"
#include "commands\CommandQueue.hpp"
#include "entities\Aircraft.hpp"
#include <ostream>

class Player{
public:
	void handleEvents(const sf::Event& event, CommandQueue& commands);
	void handleRealTimeInputs(CommandQueue& commands);
	
};

#endif