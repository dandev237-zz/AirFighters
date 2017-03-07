#pragma once

#include "ResourceIdentifiers.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <assert.h>

template <typename Resource, typename Identifier>
class ResourceManager
{
public:

	/**
		Loads a resource from memory.
		Throws std::runtime_error if the resource could not be loaded.

		secondParameter "default" value to be checked is 0. This indicates a lack of a third parameter.
	*/
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParameter);

	/**
		Get an inmutable resource.
	*/
	const Resource& get(Identifier id) const;

	/**
		Get a mutable resource.
		This function uses its const version.
	*/
	Resource& get(Identifier id);

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

//innclude "ResourceManager.inl" -- DOESN'T WORK. TODO: FIND OUT WHY

template <typename Resource, typename Identifier>
template <typename Parameter>
inline void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParameter)
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

template <typename Resource, typename Identifier>
inline const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
inline Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
	//Neat trick to avoid code duplication
	return const_cast<Resource&> (static_cast<const ResourceManager&> (*this).get(id));
}