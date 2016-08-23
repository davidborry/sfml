#include "../../headers/states/MenuState.hpp"
#include "../../headers/util/ResourceHolder.hpp"
#include "../../headers/util/Utility.hpp"
#include "../../headers/util/foreach.hpp"

MenuState::MenuState(StateStack& stack, Context context) : 
State(stack, context),
mOptions(),
mOptionIndex(0)
{
	sf::Texture& texture = context.textures->get(Resources::Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Resources::Fonts::Main);

	mBackgroundSprite.setTexture(texture);

	//A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));

	updateOptionText();

}

void MenuState::draw(){
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	FOREACH(sf::Text& text, mOptions){
		window.draw(text);
	}
	
}

bool MenuState::update(sf::Time dt){
	return true;
}

bool MenuState::handleEvent(const sf::Event& event){
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return){
		if (mOptionIndex == Play){
			requestStackPop();
			requestStackPush(States::Game);
		}

		else if (mOptionIndex == Exit)
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
	}

	else if (event.key.code == sf::Keyboard::Up){
		//Decrement and wrap around
		if (mOptionIndex > 0)
			mOptionIndex--;

		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down){
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;

		else
			mOptionIndex = 0;

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText(){
	if (mOptions.empty())
		return;

	FOREACH(sf::Text& text, mOptions)
		text.setColor(sf::Color::White);

	mOptions[mOptionIndex].setColor(sf::Color::Red);
}