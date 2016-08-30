#include "../headers/Application.hpp"

#include "../headers/states/TitleState.hpp"
#include "../headers/states/MenuState.hpp"
#include "../headers/states/LoadingState.hpp"
#include "../headers/states/GameState.hpp"
#include "../headers/states/PauseState.hpp"
#include "../headers/states/SettingsState.hpp"
#include "../headers/states/GameOverState.hpp"

#include "../headers/util/Utility.hpp"


const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application() :
mWindow(sf::VideoMode(640, 480), "States",sf::Style::Close),
mTextures(),
mFonts(),
mPlayer(),
mStateStack(State::Context(mWindow,mTextures,mFonts,mPlayer)),
mStatisticsText(),
mStatisticsUpdateTime(),
mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	
	mFonts.load(Resources::Fonts::Main, "Resources/font/Sansation.ttf");
	mTextures.load(Resources::Textures::TitleScreen, "Resources/img/TitleScreen.png");
	mTextures.load(Resources::Textures::Buttons, "Resources/img/Buttons.png");

	mStatisticsText.setFont(mFonts.get(Resources::Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
}

void Application::run(){
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()){
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TimePerFrame){
			timeSinceLastUpdate -= TimePerFrame;

			processInputs();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInputs(){
	sf::Event event;

	while (mWindow.pollEvent(event)){
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt){
	mStateStack.update(dt);
}

void Application::render(){
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt){
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f)){

		mStatisticsText.setString("FPS " +toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates(){
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<LoadingState>(States::Loading);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
	mStateStack.registerState<GameOverState>(States::GameOver);
}
