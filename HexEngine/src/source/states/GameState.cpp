#include "../../headers/states/GameState.hpp"
#include "../../headers/states//PauseState.hpp"
#include "../../headers/states/StateStack.hpp"

GameState::GameState(StateStack& stack, Context context, int param) :
State(stack, context,param),
mWorld(*context.window,*context.fonts),
mPlayer(*context.player)
{
	mPlayer.startGame();
	mPlayer.setMissionStatus(Player::MissionRunning);
}

void GameState::draw(){
	mWorld.draw();
}

bool GameState::update(sf::Time dt){
	//printf("%i\n", mParam);

	
	/*if (mWorld.gameStatus())
		mPlayer.endGame();*/

	if (!mWorld.hasActivePlayer()){
		printf("MORT");
		mPlayer.setMissionStatus(Player::MissionFailure);
		requestStackPush(States::GameOver);
	}

	else if (mWorld.hasPlayerReachedEnd()){
		mPlayer.setMissionStatus(Player::MissionSuccess);
		requestStackPush(States::GameOver);
	}

	mWorld.update(dt);
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInputs(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event){
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvents(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
		
		//mStack->registerState<PauseState>(States::Pause,8);
		requestStackPush(States::Pause);
	}

	return true;
}