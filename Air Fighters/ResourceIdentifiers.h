#pragma once

//Forward declaration of SFML classes
namespace sf {
	class Texture;
}

namespace Textures {
	enum class ID {Eagle, Raptor, Desert};
}

//Forward declarations and type definitions
template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
