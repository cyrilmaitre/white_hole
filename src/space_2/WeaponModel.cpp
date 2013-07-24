#include "WeaponModel.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_DAMAGEMULTIPLIER		"damagemultiplier"
#define CONFIG_AMMOMAX				"ammomax"
#define CONFIG_RANGE				"range"
#define CONFIG_RANGEANGLE			"rangeangle"
#define CONFIG_RELOADINGSPEED		"reloadingspeed"
#define CONFIG_FIRERATE				"firerate"
#define CONFIG_SOUNDRELOAD			"soundreload"
#define CONFIG_WEAPONTYPE			"weapontype"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WeaponModel::WeaponModel( KeyValueFile* p_config ): Item(p_config->getInt("id"))
{
	this->mWeaponType = NULL;
	this->loadFromConfig(p_config);
}

WeaponModel::~WeaponModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
double WeaponModel::getDamageMultiplier()
{
	return this->mDamageMultiplier;
}

void WeaponModel::setDamageMultiplier( double p_multiplier )
{
	this->mDamageMultiplier = p_multiplier;
}

int WeaponModel::getAmmoMax()
{
	return this->mAmmoMax;
}

void WeaponModel::setAmmoMax( int p_max )
{
	this->mAmmoMax = p_max;
}

double WeaponModel::getRange()
{
	return this->mRange;
}

void WeaponModel::setRange( double p_range )
{
	this->mRange = p_range;
}

double WeaponModel::getRangeAngle()
{
	return this->mRangeAngle;
}

void WeaponModel::setRangeAngle( double p_angle )
{
	if(p_angle < 0)
		p_angle = 0;

	this->mRangeAngle = p_angle;
}

float WeaponModel::getReloadingSpeed()
{
	return this->mReloadingSpeed;
}

void WeaponModel::setReloadingSpeed( float p_speed )
{
	this->mReloadingSpeed = p_speed;
}

float WeaponModel::getFireRate()
{
	return this->mFireRate;
}

void WeaponModel::setFireRate( float p_fireRate )
{
	this->mFireRate = p_fireRate;
}

WeaponType * WeaponModel::getWeaponType()
{
	return this->mWeaponType;
}

void WeaponModel::setWeaponType( WeaponType *p_type )
{
	this->mWeaponType = p_type;
}

std::string WeaponModel::getSoundReload()
{
	return this->mSoundReload;
}

void WeaponModel::setSoundReload( std::string p_sound )
{
	this->mSoundReload = p_sound;
}


//*************************************************************
// Methods
//*************************************************************
void WeaponModel::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_DAMAGEMULTIPLIER))
		this->setDamageMultiplier(p_config->getDouble(CONFIG_DAMAGEMULTIPLIER));
	
	if(p_config->has(CONFIG_AMMOMAX))
		this->setAmmoMax(p_config->getInt(CONFIG_AMMOMAX));

	if(p_config->has(CONFIG_RANGE))
		this->setRange(p_config->getDouble(CONFIG_RANGE));

	if(p_config->has(CONFIG_RANGEANGLE))
		this->setRangeAngle(p_config->getDouble(CONFIG_RANGEANGLE));

	if(p_config->has(CONFIG_RELOADINGSPEED))
		this->setReloadingSpeed(p_config->getFloat(CONFIG_RELOADINGSPEED));

	if(p_config->has(CONFIG_FIRERATE))
		this->setFireRate(p_config->getFloat(CONFIG_FIRERATE));

	if(p_config->has(CONFIG_SOUNDRELOAD))
		this->setSoundReload(p_config->getString(CONFIG_SOUNDRELOAD));

	if(p_config->has(CONFIG_WEAPONTYPE))
		this->setWeaponType(FactoryGet::getWeaponTypeFactory()->getWeaponType(p_config->getLong(CONFIG_WEAPONTYPE)));
}



