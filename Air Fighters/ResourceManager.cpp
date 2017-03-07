#include "ResourceManager.h"

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParameter)
{
	//Create new unique_ptr which owns the resource
	std::unique_ptr<Resource> resource(new Resource());

	//Check secondParameter validity
	if (secondParameter != 0)
	{
		resource->loadFromFile(filename, *secondParameter);
	}
	else
	{
		resource->loadFromFile(filename);
	}

	if (!resource)
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	//inserted is a pair containing an interator and a boolean value
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(ResourcePointer)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	/*
		Add const to *this so that our call to get() will call the const version
		Then, we strip the const modifier off the returned value
		This way, we avoid code duplication
	*/
	return const_cast<Resource&> (static_cast<const ResourceManager&> (*this).get(id));
}