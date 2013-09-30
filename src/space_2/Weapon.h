#pragma once
#include "CharacterShip.h"
#include "WeaponModel.h"
#include "AmmoModel.h"
#include "Entity.h"
#include "Clock.h"

// Define
#define JSON_IDWEAPON			"idWeapon"
#define JSON_AMMOCOUNT			"ammoCount"
#define JSON_ACTIF				"actif"
#define JSON_IDAMMO				"idAmmo"	
#define JSON_IDCHARACTERSHIP	"idCharacterShip"
#define JSON_IDWEAPONMODEL		"idWeaponModel"

class Weapon
{
public:
	// Constructor - Destructor
	Weapon(Json::Value json, CharacterShip *p_characterShip);
	Weapon(Entity* p_entity, WeaponModel* p_weaponModel, AmmoModel* p_ammoModel);
	void init();
	~Weapon(void);

	// Getters - Setters
	long getIdWeapon();
	void setIdWeapon(long p_id);

	AmmoModel *getAmmo();
	void setAmmo(AmmoModel *p_ammo);
	bool isAmmoChanged();
	bool hasAmmo();

	int getAmmoCount();
	void setAmmoCount(int p_ammo);
	void decAmmoCount();
	bool isAmmoCountChanged();

	bool isActif();
	void setActif(bool p_actif);

	Entity *getEntity();
	void setEntity(Entity *p_ship);

	WeaponModel *getWeaponModel();
	void setWeaponModel(WeaponModel *p_model);

	bool isReloading();
	bool isFiring();
	bool isFull();
	float getReloadTime();
	float getFireRateTime();

	bool isRangeOk();
	void setRangeOk(bool p_range);
	bool isRangeOkChanged();

	bool isAngleOk();
	void setAngleOk(bool p_angle);
	bool isAngleOkChanged();

	double getBaseDamage();
	double getDps();

	// Methods
	void update();
	void fire(Entity *p_target, Entity* p_source);
	void reload();
	void notifyAmmoChanged();
	void notifyAmmoCountChanged();
	void notifyRangeOkChanged();
	void notifyAngleOkChanged();
	void loadFromJson(Json::Value json);
	Json::Value saveToJson();


private:
	// Attributs
	long mIdWeapon;

	AmmoModel *mAmmo;
	bool mAmmoChanged;

	int mAmmoCount;
	bool mAmmoCountChanged;

	bool mActif;
	Entity *mEntity;
	WeaponModel *mWeaponModel;

	bool mRangeOk;
	bool mRangeOkChanged;

	bool mAngleOk;
	bool mAngleOkChanged;

	bool mFirstFire;
	bool mFirstReload;

	mks::Clock mFireRateClock;
	mks::Clock mRealoadClock;
};

