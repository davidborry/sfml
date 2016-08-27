#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "../util/DataTable.hpp"
#include "../scene/TextNode.hpp"

class Aircraft : public Entity{
public:
	enum Type{
		EAGLE,
		RAPTOR,
		AVENGER,
		TypeCount,
	};

public:
	
	explicit Aircraft(Type type);
	Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getCategory() const;
	float getMaxSpeed() const;


private:
	virtual void updateCurrent(sf::Time dt);
	void updateMovementPattern(sf::Time dt);

private:
	Type mType;
	sf::Sprite mSprite;

	TextNode* mHealthDisplay;

	int mDirectionIndex;
	float mTravelledDistance;
};

#endif