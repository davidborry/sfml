#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include "SFML\Graphics.hpp"
#include <memory>
#include <assert.h>


namespace Textures{
	enum ID{Landscape, Airplane, Missile};
}

template < typename Resource, typename Identifier >
class ResourceHolder{

public:
	void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename){

		unique_ptr<Resource> resource(new Resource());
		printf("dsfsdf");
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("TextureHolder::load - failed to load " + filename);

		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

	const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return *found->second;
	}

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#endif