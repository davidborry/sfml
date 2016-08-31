#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Resources{
	namespace Textures
	{
		enum ID
		{
			Entities,
			Jungle,
			Buttons,
			TitleScreen,
			Explosion,
			Particle,
			FinishLine
		};

	}

	namespace Fonts
	{
		enum ID
		{
			Main,
		};

	}

	namespace Shaders{
		enum ID{
			BrightnessPass,
			DownSamplePass,
			GaussianBlurPass,
			AddPass
		};
	}

	namespace Musics{
		enum ID{
			MenuTheme,
			MissionTheme,
		};
	}

	namespace SoundEffects{
		enum ID{
			AlliedGunfire,
			EnemyGunfire,
			Explosion1,
			Explosion2,
			LaunchMissile,
			CollectPickup,
			Button,
		};
	}
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Resources::Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Resources::Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Shader, Resources::Shaders::ID> ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, Resources::SoundEffects::ID> soundBufferHolder;

#endif // BOOK_RESOURCEID