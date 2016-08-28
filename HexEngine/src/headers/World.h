#ifndef WORLD_H
#define WORLD_H

#include "SFML\Graphics.hpp"
#include "util\ResourceHolder.hpp"
#include "util\ResourceIdentifier.hpp"
#include "scene\SceneNode.hpp"
#include "scene\SpriteNode.hpp"
#include "entities\Aircraft.hpp"
#include "commands\CommandQueue.hpp"
#include "util\Foreach.hpp"
#include "entities\Pickup.hpp"
#include <array>


class World : private sf::NonCopyable{

public:
	struct SpawnPoint{
		SpawnPoint(Aircraft::Type type, float x, float y);

		Aircraft::Type type;
		float x;
		float y;
	};

public:
	explicit World(sf::RenderWindow& window, FontHolder& fonts);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();
	bool gameStatus() const;

	bool hasActivePlayer() const;
	bool hasPlayerReachedEnd() const;

private:
	void loadTextures();
	void buildScene();

	void spawnEnemies();
	void addEnemy(Aircraft::Type type, float x, float y);
	void addEnemies();

	void adaptPlayerVelocity();
	void adaptPlayerPosition();

	sf::FloatRect getViewBounds() const;
	sf::FloatRect getBattlefieldBounds() const;
	void destroyEntitiesOutsideView();

	void guideMissiles();

	void handleCollisions();

private:
	enum Layer{
		Background,
		Air,
		LayerCount
	};

private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;
	FontHolder& mFonts;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	CommandQueue mCommandQueue;
	
	std::vector<SpawnPoint> mEnemySpointPoints;
	std::vector<Aircraft*> mActiveEnemies;

	bool gameOver;
	
};


#endif