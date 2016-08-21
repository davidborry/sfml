#include "../headers/Player.hpp"
#include <iostream>


template<typename GameObject, typename Function>
std::function<void(SceneNode&,sf::Time)>
derivedAction(Function fn){
	return[=](SceneNode& node, sf::Time dt){
		//Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		//Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

struct AircraftMover{
	AircraftMover(float vx, float vy) : velocity(vx, vy){}

	void operator() (Aircraft& aircraft, sf::Time dt) const{
		aircraft.accelerate(velocity);

	}
	sf::Vector2f velocity;
};

void Player::handleEvents(const sf::Event& event, CommandQueue& commands){
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time){
			std::cout << s.getPosition().x << ',' << s.getPosition().y << endl;
		};

		commands.push(output);
	}
}

void Player::handleRealTimeInputs(CommandQueue& commands){
	const float playerSpeed = 200.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		//printf("test");

		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		commands.push(moveLeft);

	}

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
		commands.push(moveRight);
	}

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		commands.push(moveUp);
	}
}