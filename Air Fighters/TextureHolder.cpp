#include "TextureHolder.h"
#include <assert.h>

TextureHolder::TextureHolder()
{}

TextureHolder::~TextureHolder()
{}

void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	//Create new unique_ptr which owns the texture
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename)) {
		throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
	}

	//Create a pair with a texture ID and a new unique pointer created by
	//transferring ownership to a new unique_ptr
	//inserted is a pair containing an interator and a boolean value
	auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
	assert(inserted.second);
}

const sf::Texture& TextureHolder::get(Textures::ID id) const
{
	auto found = mTextureMap.find(id);
	assert(found != mTextureMap.end());

	return *found->second;
}

sf::Texture& TextureHolder::get(Textures::ID id)
{
	/*
	  Add const to *this so that our call to get() will call the const version
	  Then, we strip the const modifier off the returned value
	  This way, we avoid code duplication
	*/
	return const_cast<sf::Texture&> (static_cast<const TextureHolder&> (*this).get(id));
}