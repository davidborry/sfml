#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <SFML\Graphics.hpp>
#include "../commands/Command.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {

public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	virtual unsigned int getCategory() const;

	void onCommand(const Command& command, sf::Time dt);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

#endif