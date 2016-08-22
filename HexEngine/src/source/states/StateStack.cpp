#include "../../headers/states/StateStack.hpp"

StateStack::StateStack(State::Context context) : mStack(), mPendingList(), mFactories(), mContext(context)
{

}

template<typename T>
void StateStack::registerState(States::ID stateID){
	mFactories[stateID] = [this]() {
		return State::Ptr(new T(*this, mContext));
	}
}

State::Ptr StateStack::createState(States::ID stateID){
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::handleEvent(const sf::Event& event){
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		if (!(*itr)->handleEvent(event))
			break;

	applyPendingChanges();
}

void StateStack::update(sf::Time dt){
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
		if (!(*itr)->update(dt))
			break;

	applyPendingChanges();
}

void StateStack::draw(){
	FOREACH(State::Ptr& state, mStack)
		state->draw();
}

void StateStack::applyPendingChanges(){
	FOREACH(PendingChange change, mPendingList){
		switch (change.action){
		case Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
		
}

void StateStack::pushState(States::ID stateID){
	mPendingList.push_back(PendingChange(Push,stateID));
}

void StateStack::popState(){
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates(){
	mPendingList.push_back(PendingChange(Clear));
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID) : action(action), stateID(stateID)
{

}