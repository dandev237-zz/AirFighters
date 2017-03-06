#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

namespace Textures
{
	enum class ID { Landscape, Airplane, Missile };
}

class TextureHolder
{
public:
	TextureHolder();
	~TextureHolder();

	/**
		Loads a texture from memory.
	*/
	void load(Textures::ID id, const std::string& filename);

	/**
		Gets an inmutable texture.
	*/
	const sf::Texture& get(Textures::ID id) const;

	/**
		Gets a mutable texture.
		This function uses its const version.
	*/
	sf::Texture& get(Textures::ID id);

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

