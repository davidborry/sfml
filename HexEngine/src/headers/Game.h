#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "util\ResourceHolder.hpp"
#include "util\ResourceIdentifier.hpp"
#include "entities\Aircraft.hpp"
#include <iostream>

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
	Aircraft* mPlayer;

	sf::Text mText;

	float playerSpeed = 100.f;
	bool isAccelerating=false, isSlowingDown=false, isRotatingLeft = false, isRotatingRight=false;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	ResourceHolder<sf::Texture, Textures::ID> textures;
	ResourceHolder<sf::Font, Fonts::ID> fonts;

	sf::View mWorldView;

};

#endif