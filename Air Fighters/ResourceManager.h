#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <assert.h>

#include "ResourceIdentifiers.h"

template <typename Resource, typename Identifier>
class ResourceManager
{
public:

	/**
	Loads a resource from memory.
	Throws std::runtime_error if the resource could not be loaded.
	*/
	void load(Identifier id, const std::string& filename);

	/**
		Loads a resource from memory. Overloaded version of "load()" with an aditional parameter.
		Throws std::runtime_error if the resource could not be loaded.
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

	/**
		Helper function. Inserts a new resource in the resource map.
		Throws std::runtime_error if the resource could not be loaded or if it is invalid.
	*/
	void insertResource(std::unique_ptr<Resource> resource, Identifier id);
};

//include "ResourceManager.inl" -- DOESN'T WORK. TODO: FIND OUT WHY

template<typename Resource, typename Identifier>
inline void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	//Create new unique_ptr which owns the resource
	std::unique_ptr<Resource> resource(new Resource());
	resource->loadFromFile(filename);

	if (!resource)
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	insertResource(std::move(resource), id);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
inline void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParameter)
{
	std::unique_ptr<Resource> resource(new Resource());
	resource->loadFromFile(filename, secondParameter);

	if (!resource)
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	insertResource(std::move(resource), id);
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

template<typename Resource, typename Identifier>
inline void ResourceManager<Resource, Identifier>::insertResource(std::unique_ptr<Resource> resource, Identifier id)
{

	//inserted is a pair containing an interator and a boolean value
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}