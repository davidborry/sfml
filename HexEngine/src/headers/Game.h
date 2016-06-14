#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "util\ResourceHolder.h"


class Game{

public:
	Game();
	void run();
	
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void movePlayer(sf::Time deltaTime);

	sf::RenderWindow mWindow;
	sf::Sprite mPlayer;

	float playerSpeed = 100.f;
	bool isAccelerating=false, isSlowingDown=false, isRotatingLeft = false, isRotatingRight=false;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	ResourceHolder textures;

};

#endif