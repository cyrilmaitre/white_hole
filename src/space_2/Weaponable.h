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

	int getWeaponSlot();
	Weapon *getWeapon(int p_index);

	// Methods
	void update();
	void addWeapon(Weapon *p_weapon);
	void removeWeapon(Weapon *p_weapon);
	void removeWeapon(int p_index);
	void fire(Entity *p_target, Entity *p_source);
	void reload();


private:
	// Attributs
	std::vector<Weapon*> mWeapons;
};

