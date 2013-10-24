#pragma once
#include "CharacterShip.h"
#include "WeaponModel.h"
#include "AmmoModel.h"
#include "Entity.h"
#include "Clock.h"


class Weapon
{
public:
	// Constructor - Destructor
	Weapon(void);
	Weapon(Json::Value json, CharacterShip *p_characterShip);
	Weapon(Entity* p_entity, WeaponModel* p_weaponModel, AmmoModel* p_ammoModel);
	Weapon(CharacterShip* p_ship, WeaponModel* p_model);
	void init();
	~Weapon(void);

	// Getters - Setters
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
	mks::Clock mReloadClock;
};

