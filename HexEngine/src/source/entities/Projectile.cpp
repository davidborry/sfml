#include "../../headers/entities/Projectile.hpp"

namespace{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Projectile::Type type, const TextureHolder& textures):
Entity(1),
mType(type),
mSprite(textures.get(Table[type].texture))
{
	centerOrigin(mSprite);
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands){
	Entity::updateCurrent(dt,commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const {
	if (mType == Projectile::Type::EnemyBullet)
		return Category::EnemyProjectile;

	else
		return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const {
	return mSprite.getGlobalBounds();
}

float Projectile::getMaxSpeed() const {
	return Table[mType].speed;
}