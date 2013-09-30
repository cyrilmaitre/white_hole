#include "Weapon.h"
#include "FactoryGet.h"
#include "Game.h"
#include "AutoManager.h"
#include "Impact.h"
#include "ProjectileManager.h"
#include "Juckebox.h"
#include "ToolsMap.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Weapon::Weapon( Json::Value json, CharacterShip *p_characterShip )
{
	this->init();
	this->setEntity(p_characterShip);
	this->loadFromJson(json);
}

Weapon::Weapon( Entity* p_entity, WeaponModel* p_weaponModel, AmmoModel* p_ammoModel )
{
	this->init();
	this->setEntity(p_entity);
	this->setWeaponModel(p_weaponModel);
	this->setAmmo(p_ammoModel);
}

void Weapon::init()
{
	this->mWeaponModel = NULL;
	this->mEntity = NULL;
	this->mAmmo = NULL;

	this->mId = -1;
	this->mAmmoChanged = false;
	this->mAmmoCount = 0;
	this->mAmmoCountChanged = false;
	this->mActif = true;

	this->mRangeOk = false;
	this->mRangeOkChanged = false;

	this->mAngleOk = false;
	this->mAngleOkChanged = false;

	this->mFirstFire = true;
	this->mFirstReload = true;
}

Weapon::~Weapon(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long Weapon::getId()
{
	return this->mId;
}

void Weapon::setId( long p_id )
{
	this->mId = p_id;
}

AmmoModel * Weapon::getAmmo()
{
	return this->mAmmo;
}

void Weapon::setAmmo( AmmoModel *p_ammo )
{
	if(this->mAmmo != p_ammo)
	{
		this->mAmmo = p_ammo;
		this->notifyAmmoChanged();
	}
}

bool Weapon::isAmmoChanged()
{
	bool returnValue = this->mAmmoChanged;
	this->mAmmoChanged = false;
	return returnValue;
}

bool Weapon::hasAmmo()
{
	return this->mAmmo != NULL && this->mAmmoCount > 0;
}

int Weapon::getAmmoCount()
{
	return this->mAmmoCount;
}

void Weapon::setAmmoCount( int p_ammo )
{
	if(p_ammo < 0)
		p_ammo = 0;
	else if(this->getWeaponModel() != NULL && p_ammo > this->getWeaponModel()->getAmmoMax())
		p_ammo = this->getWeaponModel()->getAmmoMax();

	if(this->mAmmoCount != p_ammo)
	{
		this->mAmmoCount = p_ammo;
		this->notifyAmmoCountChanged();
	}
}

void Weapon::decAmmoCount()
{
	this->setAmmoCount(this->getAmmoCount() - 1);
}

bool Weapon::isAmmoCountChanged()
{
	bool returnValue = this->mAmmoCountChanged;
	this->mAmmoCountChanged = false;
	return returnValue;
}

bool Weapon::isActif()
{
	return this->mActif;
}

void Weapon::setActif( bool p_actif )
{
	this->mActif = p_actif;
}

Entity * Weapon::getEntity()
{
	return this->mEntity;
}

void Weapon::setEntity( Entity *p_ship )
{
	this->mEntity = p_ship;
}

WeaponModel * Weapon::getWeaponModel()
{
	return this->mWeaponModel;
}

void Weapon::setWeaponModel( WeaponModel *p_model )
{
	this->mWeaponModel = p_model;
}

bool Weapon::isReloading()
{
	return this->mRealoadClock.getElapsedTimeAsSeconds() < this->getWeaponModel()->getReloadingSpeed() && !this->mFirstReload;
}

bool Weapon::isFiring()
{
	return this->mFireRateClock.getElapsedTimeAsSeconds() < this->getWeaponModel()->getFireRate() && !this->mFirstFire;
}

bool Weapon::isFull()
{
	return this->getAmmoCount() == this->getWeaponModel()->getAmmoMax();
}

float Weapon::getReloadTime()
{
	return this->mRealoadClock.getElapsedTimeAsSeconds();
}

float Weapon::getFireRateTime()
{
	return this->mFireRateClock.getElapsedTimeAsSeconds();
}

bool Weapon::isRangeOk()
{
	return this->mRangeOk;
}

void Weapon::setRangeOk( bool p_range )
{
	if(this->mRangeOk != p_range)
	{
		this->mRangeOk = p_range;
		this->notifyRangeOkChanged();
	}
}

bool Weapon::isRangeOkChanged()
{
	bool returnValue = this->mRangeOkChanged;
	this->mRangeOkChanged = false;
	return returnValue;
}

bool Weapon::isAngleOk()
{
	return this->mAngleOk;
}

void Weapon::setAngleOk( bool p_angle )
{
	if(this->mAngleOk != p_angle)
	{
		this->mAngleOk = p_angle;
		this->notifyAngleOkChanged();
	}
}

bool Weapon::isAngleOkChanged()
{
	bool returnValue = this->mAngleOkChanged;
	this->mAngleOkChanged = false;
	return returnValue;
}

double Weapon::getBaseDamage()
{
	return this->getAmmo()->getDamage() * this->getWeaponModel()->getDamageMultiplier();
}

double Weapon::getDps()
{
	return this->getBaseDamage() / this->getWeaponModel()->getFireRate();
}


//*************************************************************
// Methods
//*************************************************************
void Weapon::loadFromJson( Json::Value json )
{
	if(ToolsMap::isCharacterShip(this->getEntity()))
	{
		CharacterShip* characterShip = (CharacterShip*)this->getEntity();

		this->setId(json.get(JSON_IDWEAPON, -1).asInt());
		long ammoId = json.get(JSON_IDAMMO, -1).asInt();
		if(ammoId != -1)
			this->setAmmo(FactoryGet::getAmmoFactory()->getAmmo(ammoId));
		else
			this->setAmmo(NULL);
		this->setAmmoCount(json.get(JSON_AMMOCOUNT, 0).asInt());
		this->setActif(json.get(JSON_ACTIF, true).asBool());
		this->setWeaponModel(FactoryGet::getWeaponModelFactory()->getWeaponModel(json.get(JSON_IDWEAPONMODEL, -1).asInt()));
	}	
}

Json::Value Weapon::saveToJson()
{
	Json::Value json;
	if(ToolsMap::isCharacterShip(this->getEntity()))
	{
		CharacterShip* characterShip = (CharacterShip*)this->getEntity();
		
		json[JSON_IDWEAPON] = this->getId();
		if(this->getAmmo() != NULL)
			json[JSON_IDAMMO] = this->getAmmo()->getIdItem();
		else
			json[JSON_IDAMMO] = -1;
		json[JSON_AMMOCOUNT] = this->getAmmoCount();
		json[JSON_ACTIF] = this->isActif();
		json[JSON_IDCHARACTERSHIP] = characterShip->getIdCharacterShip();
		json[JSON_IDWEAPONMODEL] = this->getWeaponModel()->getIdItem();
	}
	return json;
}

void Weapon::notifyAmmoChanged()
{
	this->mAmmoChanged = true;
}

void Weapon::notifyAmmoCountChanged()
{
	this->mAmmoCountChanged = true;
}

void Weapon::notifyRangeOkChanged()
{
	this->mRangeOkChanged = true;
}

void Weapon::notifyAngleOkChanged()
{
	this->mAngleOkChanged = true;
}

void Weapon::fire( Entity* p_target, Entity* p_source )
{
	if(	!this->isActif() || this->isFiring() || this->isReloading() || !this->isRangeOk() || !this->isAngleOk())
		return;

	this->mFirstFire = false;

	// TODO: Play sound with level in function of distance
	//Resource::resource->getJuckebox()->soundPlay(this->getWeaponModel()->getSoundFire());

	AutoManager::add(ProjectileManager::getProjectile(p_source, p_target, this));

	this->decAmmoCount();
	this->mFireRateClock.restart();
}

void Weapon::update()
{
	if(this->getAmmoCount() == 0)
		this->reload();

	if(this->getEntity() != NULL && this->getEntity()->getTarget()->isEntityValid())
	{
		this->setRangeOk(	this->getEntity() != this->getEntity()->getTarget()->getEntity() &&
							ToolsMap::getDistance(this->getEntity(), this->getEntity()->getTarget()->getEntity()) < this->getWeaponModel()->getRange());
		this->setAngleOk(	this->getEntity() != this->getEntity()->getTarget()->getEntity() &&
							ToolsMap::getAngle(this->getEntity(), this->getEntity()->getTarget()->getEntity()) < this->getWeaponModel()->getRangeAngle());
	}
}

void Weapon::reload()
{
	if( !this->isActif() || this->isReloading() || this->isFull() )
		return;

	this->mFirstReload = false;

	if(ToolsMap::isCharacterShip(this->getEntity()))
	{
		Resource::resource->getJuckebox()->soundPlay(this->getWeaponModel()->getSoundReload());
		this->setAmmoCount(this->getWeaponModel()->getAmmoMax());
	}
	else
	{
		this->setAmmoCount(this->getWeaponModel()->getAmmoMax());
	}

	this->mRealoadClock.restart();
}








