#ifndef GAME_H
#define GAME_H

#include "World.h"
#include "util\Category.hpp"
#include "Player.hpp"

#include <iostream>

class Game{

public:
	Game();
	void run();
	
private:
	void processInputs();
	void update(sf::Time deltaTime);
	void render();
	void movePlayer(sf::Time deltaTime);

	void handleKeyEvent(sf::Keyboard::Key event);

	sf::RenderWindow mWindow;
	//Aircraft* mPlayer;

	sf::Text mText;

	float playerSpeed = 100.f;
	bool isAccelerating=false, isSlowingDown=false, isRotatingLeft = false, isRotatingRight=false;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	ResourceHolder<sf::Texture, Textures::ID> textures;
	ResourceHolder<sf::Font, Fonts::ID> fonts;

	sf::View mWorldView;

	World mWorld;

	bool mPaused;

	Player mPlayer;

};

#endif