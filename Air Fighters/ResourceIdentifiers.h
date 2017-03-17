#pragma once

//Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum class ID { Eagle, Raptor, Desert };
}

namespace Fonts
{
	enum class ID { Main };
}

//Forward declarations and type definitions
template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
