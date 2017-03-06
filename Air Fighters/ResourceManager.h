#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <assert.h>

template <typename Resource, typename Identifier>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	/**
	Loads a resource from memory.
	Throws std::runtime_error if the resource could not be loaded.

	secondParameter "default" value to be checked is 0. This indicates a lack of a third parameter.
	*/
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParameter);

	/**
	Gets an inmutable resource.
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

