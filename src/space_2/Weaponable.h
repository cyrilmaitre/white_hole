#pragma once
#include "Resource.h"
#include "WeaponableData.h"

class Entity;
class Weapon;

class Weaponable: public WeaponableData
{
public:
	// Constructor - Destructor
	Weaponable(void);
	~Weaponable(void);

	// Getters - Setters
	bool isWeaponFull();
	bool isWeaponEmpty();

	int getWeaponsCount();
	Weapon *getWeapon(int p_index);

	// Methods
	void update();
	void addWeapon(Weapon *p_weapon, bool p_notify = true);
	void removeWeapon(Weapon *p_weapon, bool p_notify = true);
	void removeWeapon(int p_index, bool p_notify = true);
	void removeWeaponAll(bool p_notify = true);
	void fire(Entity *p_target, Entity *p_source);
	void reload();
	virtual void notifyWeaponsChanged();


private:
	// Attributs
	std::vector<Weapon*> mWeapons;
};

