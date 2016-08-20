#include "../headers/Game.h"

using namespace std;

Game::Game() : mWindow(sf::VideoMode(640, 480), "My Game"), mWorld(mWindow), mText(), mWorldView(), mPaused(false) {

	textures.load(Textures::Eagle, "Resources/img/plane.png");
	textures.load(Textures::Desert, "Resources/img/sand.jpg");
	fonts.load(Fonts::Pacifico, "Resources/font/Pacifico.ttf");

	mWindow.setFramerateLimit(60);
	mWindow.setVerticalSyncEnabled(true);
	
	mPlayer = new Aircraft(Aircraft::Type::EAGLE, textures);

	cout << mWorldView.getSize().x << endl;

	mWorldView.setCenter(100.f,0.f);
	mPlayer->setPosition(100.f, 0.f);

	//mWorldView.setSize(1024, 720);
	//mWorldView.zoom(0.52);
	
	sf::Font a = fonts.get(Fonts::Pacifico);
	mText.setFont(fonts.get(Fonts::Pacifico));
	mText.setString("Test");
	mText.setColor(sf::Color::Red);
	mText.setPosition(0, 0);

	/**mWindow.setView(mWorldView);

	mWindow.clear();
	mWindow.draw(*mPlayer);
	mWindow.draw(mText);
	mWindow.display();**/

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
			
			if (!mPaused)
				update(TimePerFrame);

			processEvents();
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
			handleKeyEvent(event.key.code);
			break;

		case sf::Event::LostFocus:
			mPaused = true;
			break;

		case sf::Event::GainedFocus:
			mPaused = false;
			break;
		}

	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2i windowCenter(mWindow.getSize() / 2u);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	sf::Vector2i delta = windowCenter - mousePosition;
	sf::Mouse::setPosition(windowCenter, mWindow);
	//printf("%i - %i\n",delta.x,delta.y);
	mWorld.update(deltaTime);
	/*sf::Vector2f movement(0.f, 0.f);
	if (isAccelerating && playerSpeed < 300)
		playerSpeed += 1.f;

	if (isSlowingDown && playerSpeed >= 1)
		playerSpeed -= 1.f;

	if (isRotatingLeft)
		mPlayer->rotate(1.f*playerSpeed*deltaTime.asSeconds());
	
	if (isRotatingRight)
		mPlayer->rotate(-1.f*playerSpeed*deltaTime.asSeconds());

	movePlayer(deltaTime);*/

		
}

void Game::render()
{

	mWindow.clear();
	mWorld.draw();
	mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(*mPlayer);
	//mWindow.draw(mText);

	//	cout << mPlayer->getWorldPosition().x << "-" << mPlayer->getWorldPosition().y << endl;
	mWindow.display();

}

void Game::movePlayer(sf::Time deltaTime){
	
	float angleRad = (3.1415926536f / 180.f)*(mPlayer->getRotation());
	float cosT = playerSpeed * cos(angleRad);
	float sinT = playerSpeed * sin(angleRad);


	//printf("%f - x:%f -y:%f\n", mPlayer.getRotation(),cosT,sinT);

	sf::Vector2f a(0.f, 0.f);
	a.x -= sinT;
	a.y += cosT;
	mPlayer->move(a *  deltaTime.asSeconds());

	//mWorldView.setRotation(mPlayer->getRotation());
	mWorldView.move(a * deltaTime.asSeconds());

}

void Game::handleKeyEvent(sf::Keyboard::Key key){
	if (key == sf::Keyboard::Space){
		mPaused = !mPaused;
	}
}