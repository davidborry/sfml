#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML\Graphics.hpp"
#include "commands\CommandQueue.hpp"
#include "entities\Aircraft.hpp"
#include <ostream>
#include "util\foreach.hpp"

class Player{
public:
	Player();

public:

	enum Action{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		ActionCount
	};

	void handleEvents(const sf::Event& event, CommandQueue& commands);
	void handleRealTimeInputs(CommandQueue& commands);

	void assignKey(sf::Keyboard::Key key, Action action);
	sf::Keyboard::Key getAssignedKey(Action action) const;

private:
	void initializeActions();
	bool isRealTimeAction(Action action);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command> mActionBinding;
	
};

#endif