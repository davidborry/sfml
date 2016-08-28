#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category{
	enum Type{
		None = 0,
		SceneAirLayer = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
		EnemyProjectile = 1 << 4,
		AlliedProjectile = 1 << 5,
		Pickup = 1 << 6,

		Projectile = AlliedProjectile | EnemyProjectile,
		Aircraft = EnemyAircraft | PlayerAircraft | AlliedAircraft
	};
}

#endif