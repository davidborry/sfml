#include "../../headers/scene/SceneNode.hpp"
#include "../../headers/commands/Command.hpp"
#include "../../headers/util/Utility.hpp"

SceneNode::SceneNode(Category::Type category) : 
mDefaultCategory(category),
mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child){
	//printf("node");
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node){

	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr & p) -> bool {
		return p.get() == &node;
	});

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);

	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
	
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr){
		(*itr)->draw(target, states);
	}
}

void SceneNode::update(sf::Time dt, CommandQueue& commands){
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands){}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands){
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr){
		(*itr)->update(dt, commands);
	}
}

sf::Transform SceneNode::getWorldTransform() const{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform()*transform;

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const{
	return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const{
	return mDefaultCategory;
}

void SceneNode::onCommand(const Command& command, sf::Time dt){
	if (command.category & getCategory())
		command.action(*this, dt);

	for (auto child = mChildren.begin(); child != mChildren.end(); ++child)
		(*child)->onCommand(command, dt);
}

float distance(const SceneNode& lhs, const SceneNode& rhs){
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}