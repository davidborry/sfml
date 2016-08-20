#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML\Graphics.hpp"
#include "commands\CommandQueue.hpp"

class Player{
public:
	void handleEvents(const sf::Event& event, CommandQueue& commands);
	void handleRealTimeInputs(CommandQueue& commands);
};

#endif