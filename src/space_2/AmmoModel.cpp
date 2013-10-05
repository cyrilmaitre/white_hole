#include "AmmoModel.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define AMMOMODEL_CONFIG_LIFETIME			"lifeTime"
#define AMMOMODEL_CONFIG_DAMAGE				"damage"
#define AMMOMODEL_CONFIG_SPLASHRADIUS		"splashradius"
#define AMMOMODEL_CONFIG_PROJECTILETYPE		"projectile_type"
#define AMMOMODEL_CONFIG_PROJECTILECOLOR	"projectile_color"
#define AMMOMODEL_CONFIG_PROJECTILESCALE	"projectile_scale"
#define AMMOMODEL_CONFIG_SOUNDFIRE			"sound_fire"
#define AMMOMODEL_CONFIG_AMMOTYPE			"ammotype"


//*************************************************************
// Constructor - Destructor
//*************************************************************
AmmoModel::AmmoModel(KeyValueFile* p_config): Item(p_config->getInt("id"))
{
	this->mAmmoType = NULL;
	this->loadFromConfig(p_config);
}

AmmoModel::~AmmoModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long AmmoModel::getLifeTime()
{
	return this->mLifeTime;
}

void AmmoModel::setLifeTime( long p_lifeTime )
{
	this->mLifeTime = p_lifeTime;
}

double AmmoModel::getDamage()
{
	return this->mDamage;
}

void AmmoModel::setDamage( double p_damage )
{
	this->mDamage = p_damage;
}

double AmmoModel::getSplashRadius()
{
	return this->mSplashRadius;
}

void AmmoModel::setSplashRadius( double p_radius )
{
	this->mSplashRadius = p_radius;
}

Projectile::ProjectileType AmmoModel::getProjectileType()
{
	return this->mProjectileType;
}

void AmmoModel::setProjectileType( Projectile::ProjectileType p_type )
{
	this->mProjectileType = p_type;
}

std::string AmmoModel::getProjectileColor()
{
	return this->mProjectileColor;
}

void AmmoModel::setProjectileColor( std::string p_color )
{
	this->mProjectileColor = p_color;
}

float AmmoModel::getProjectileScale()
{
	return this->mProjectileScale;
}

void AmmoModel::setProjectileScale( float p_scale )
{
	this->mProjectileScale = p_scale;
}

std::string AmmoModel::getSoundFire()
{
	return this->mSoundFire;
}

void AmmoModel::setSoundFire( std::string p_sound )
{
	this->mSoundFire = p_sound;
}

AmmoType* AmmoModel::getAmmoType()
{
	return this->mAmmoType;
}

void AmmoModel::setAmmoType( AmmoType* p_type )
{
	this->mAmmoType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void AmmoModel::loadFromConfig( KeyValueFile* p_config )
{
	this->MovableData::loadFromConfig(p_config);

	if(p_config->has(AMMOMODEL_CONFIG_LIFETIME))
		this->setLifeTime(p_config->getLong(AMMOMODEL_CONFIG_LIFETIME));

	if(p_config->has(AMMOMODEL_CONFIG_DAMAGE))
		this->setDamage(p_config->getDouble(AMMOMODEL_CONFIG_DAMAGE));
	
	if(p_config->has(AMMOMODEL_CONFIG_SPLASHRADIUS))
		this->setSplashRadius(p_config->getDouble(AMMOMODEL_CONFIG_SPLASHRADIUS));

	if(p_config->has(AMMOMODEL_CONFIG_SOUNDFIRE))
		this->setSoundFire(p_config->getString(AMMOMODEL_CONFIG_SOUNDFIRE));

	if(p_config->has(AMMOMODEL_CONFIG_AMMOTYPE))
		this->setAmmoType(FactoryGet::getAmmoTypeFactory()->getAmmoType(p_config->getLong(AMMOMODEL_CONFIG_AMMOTYPE)));

	if(p_config->has(AMMOMODEL_CONFIG_PROJECTILETYPE))
		this->setProjectileType((Projectile::ProjectileType)p_config->getInt(AMMOMODEL_CONFIG_PROJECTILETYPE));

	if(p_config->has(AMMOMODEL_CONFIG_PROJECTILECOLOR))
		this->setProjectileColor(p_config->getString(AMMOMODEL_CONFIG_PROJECTILECOLOR));

	if(p_config->has(AMMOMODEL_CONFIG_PROJECTILESCALE))
		this->setProjectileScale(p_config->getFloat(AMMOMODEL_CONFIG_PROJECTILESCALE));
}










