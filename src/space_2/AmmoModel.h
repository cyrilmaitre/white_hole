#pragma once
#include "Item.h"
#include "AmmoType.h"
#include "SpriteParameter.h"
#include "MovableData.h"
#include "Projectile.h"


class AmmoModel: public Item, public MovableData
{
public:
	// Constructor - Destructor
	AmmoModel(KeyValueFile* p_config);
	~AmmoModel(void);

	// Getters - Setters
	long getLifeTime();
	void setLifeTime(long p_lifeTime);

	double getDamage();
	void setDamage(double p_damage);

	double getSplashRadius();
	void setSplashRadius(double p_radius);

	Projectile::ProjectileType getProjectileType();
	void setProjectileType(Projectile::ProjectileType p_type);

	std::string getProjectileColor();
	void setProjectileColor(std::string p_color);

	float getProjectileScale();
	void setProjectileScale(float p_scale);

	std::string getSoundFire();
	void setSoundFire(std::string p_sound);

	AmmoType* getAmmoType();
	void setAmmoType(AmmoType* p_type);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mLifeTime;
	double mDamage;
	double mSplashRadius;
	Projectile::ProjectileType mProjectileType;
	std::string mProjectileColor;
	float mProjectileScale;
	std::string mSoundFire;
	AmmoType* mAmmoType;
};

