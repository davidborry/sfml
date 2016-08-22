#include "SFML\Graphics.hpp"
#include "State.hpp"
#include <functional>

class StateStack : public sf::NonCopyable{
public:
	enum Action{
		Push,
		Pop,
		Clear
	};

public:
	explicit StateStack(State::Context context);

	template<typename T> 
	void registerState(States::ID stateId);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(States::ID stateId);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Ptr createState(States::ID stateId);
	void applyPendingChanges();

private:
	struct PendingChanges{
		explicit PendingChanges(Action action, States::ID stateID = States::None);

		Action action;
		States::ID stateID;
	};

private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChanges> mPendingList;
	State::Context mContext;
	std::map < States::ID, std::function<State::Ptr()>> mFactories;
};