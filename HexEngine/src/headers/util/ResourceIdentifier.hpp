#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
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
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Resources::Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Resources::Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Shader, Resources::Shaders::ID> ShaderHolder;

#endif // BOOK_RESOURCEID