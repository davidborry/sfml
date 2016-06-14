#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "SFML\Graphics.hpp"
#include <memory>


namespace Textures{
	enum ID{Landscape, Airplane, Missile};
}

class ResourceHolder{

public:
	void load(Textures::ID id, std::string const& filename);
	const sf::Texture& get(Textures::ID id) const;
private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif