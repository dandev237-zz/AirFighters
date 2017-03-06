#include "TextureHolder.h"

TextureHolder::TextureHolder()
{}

TextureHolder::~TextureHolder()
{}

void TextureHolder::load(Textures::ID id, const std::string& filename)
{
	//Create new unique_ptr which owns the texture
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	texture->loadFromFile(filename);

	//Create a pair with a texture ID and a new unique pointer created by
	//transferring ownership from our previously created smart pointer to
	//a new one
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

const sf::Texture& TextureHolder::get(Textures::ID id) const
{
	auto found = mTextureMap.find(id);
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