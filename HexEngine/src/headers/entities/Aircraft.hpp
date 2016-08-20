#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"

class Aircraft : public Entity{
public:
	enum Type{
		EAGLE,
		RAPTOR,
		DEFAULT,
	};

public:
	
	explicit Aircraft(Type type);
	Aircraft(Type type, TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual unsigned int getCategory() const;

private:
	Type mType;
	sf::Sprite mSprite;
};

#endif