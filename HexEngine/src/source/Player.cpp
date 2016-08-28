#include "../headers/Player.hpp"
#include <iostream>

Player::Player():
gameOver(false)
{
	mKeyBinding[sf::Keyboard::Q] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::D] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Z] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::S] = Action::MoveDown;
	mKeyBinding[sf::Keyboard::Space] = Action::Fire;

	initializeActions();

	FOREACH(auto& pair, mActionBinding){
		pair.second.category = Category::PlayerAircraft;
	}

}


struct AircraftMover{
	AircraftMover(float vx, float vy) : velocity(vx, vy){}

	void operator() (Aircraft& aircraft, sf::Time dt) const{
		aircraft.accelerate(velocity);

	}
	sf::Vector2f velocity;
};

void Player::handleEvents(const sf::Event& event, CommandQueue& commands){
	if (event.type == sf::Event::KeyReleased){
		if (event.key.code == sf::Keyboard::P){
			Command output;
			output.category = Category::PlayerAircraft;
			output.action = [](SceneNode& s, sf::Time){
				std::cout << s.getPosition().x << ',' << s.getPosition().y << endl;
			};

			commands.push(output);
		}

		else if (event.key.code == sf::Keyboard::LShift){
			Command missile;
			missile.category = Category::PlayerAircraft;
			missile.action = derivedAction<Aircraft>([](Aircraft& a, sf::Time dt)
			{
				a.launchMissile();
			});

			commands.push(missile);
		}
	}
}


void Player::handleRealTimeInputs(CommandQueue& commands){
	//printf("%i\n", gameOver);
	if (!gameOver)
	FOREACH(auto& pair, mKeyBinding)
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);

}

void Player::initializeActions(){
	const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
	mActionBinding[Fire].action = derivedAction<Aircraft>([](Aircraft& a, sf::Time dt) { a.fire(); });
}

bool Player::isRealTimeAction(Action action){
	switch (action){
	case MoveLeft:
	case MoveRight:
	case MoveUp:
	case MoveDown:
	case Fire:
		return true;

	default:
		return false;
	}
}

void Player::assignKey(sf::Keyboard::Key key, Action action){
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();){
		if (itr->second == action)
			mKeyBinding.erase(itr++);

		else
			itr++;
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const{
	FOREACH(auto pair, mKeyBinding)
		if (pair.second == action)
			return pair.first;

	return sf::Keyboard::Unknown;
	
}

void Player::endGame(){
	gameOver = true;
}

void Player::startGame(){
	gameOver = false;
}