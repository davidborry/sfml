#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

namespace Resources{
	namespace Textures
	{
		enum ID
		{
			Eagle,
			Raptor,
			Desert,
			Avenger,
			Bullet,
			Missile,
			FireRate,
			HealthRefill,
			MissileRefill,
			FireSpread,
			TitleScreen,
			ButtonNormal,
			ButtonPressed,
			ButtonSelected
		};

	}

	namespace Fonts
	{
		enum ID
		{
			Main,
		};

	}
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Resources::Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Resources::Fonts::ID> FontHolder;

#endif // BOOK_RESOURCEID