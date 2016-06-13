#include "../headers/Game.h"

using namespace std;

Game::Game() : mWindow(sf::VideoMode(640, 480), "My Game"), mPlayer(), mTexture(){

	
	
	if (!mTexture.loadFromFile("Resources/img/plane.png"))
	{
		printf("ERROR");// Handle loading error
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);

	mPlayer.setOrigin(mTexture.getSize().x/2.f, mTexture.getSize().y/2.f);

	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();

}

void Game::run(){
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}

}

void Game::processEvents(){
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		
		switch (event.type){
		case sf::Event::Closed:
			mWindow.close();
			break;

		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (isAccelerating && playerSpeed < 300)
		playerSpeed += 1.f;

	if (isSlowingDown && playerSpeed >= 1)
		playerSpeed -= 1.f;

	if (isRotatingLeft)
		mPlayer.rotate(1.f*playerSpeed*deltaTime.asSeconds());
	
	if (isRotatingRight)
		mPlayer.rotate(-1.f*playerSpeed*deltaTime.asSeconds());

	movePlayer(deltaTime);
	
	
}

void Game::render()
{
	

	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z)
		isAccelerating = isPressed;
	else if (key == sf::Keyboard::S)
		isSlowingDown = isPressed;
	else if (key == sf::Keyboard::Q)
		isRotatingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		isRotatingRight = isPressed;
}

void Game::movePlayer(sf::Time deltaTime){
	
	float angleRad = (3.1415926536 / 180)*(mPlayer.getRotation());
	float cosT = playerSpeed * cos(angleRad);
	float sinT = playerSpeed * sin(angleRad);


	//printf("%f - x:%f -y:%f\n", mPlayer.getRotation(),cosT,sinT);

	sf::Vector2f a(0.f, 0.f);
	a.x -= sinT;
	a.y += cosT;
	mPlayer.move(a *  deltaTime.asSeconds());
}