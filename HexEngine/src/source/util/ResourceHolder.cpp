#include "../../headers/util/ResourceHolder.h"

using namespace std;

void ResourceHolder::load(Textures::ID id, const string& filename){

	unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);
	texture->setSmooth(true);

	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

const sf::Texture& ResourceHolder::get(Textures::ID id) const{
	auto found = mTextureMap.find(id);
	return *found->second;
}