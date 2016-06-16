#include "../../headers/entities/Aircraft.hpp"

Textures::ID toTextureID(Aircraft::Type id){
	switch (id){
	case Aircraft::Type::EAGLE:
		return Textures::Eagle;

	case Aircraft::Type::RAPTOR:
		return Textures::Raptor;

	case Aircraft::Type::DEFAULT:
		return Textures::Airplane;
	}
}

Aircraft::Aircraft(Type type): mType(type){}

Aircraft::Aircraft(Type type, TextureHolder& textures): mType(type), mSprite(textures.get(toTextureID(type))) {
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}

