#pragma once
#include "MapObject.h"
#include "DestructableData.h"
#include "Clock.h"

// Define	
#define DESTRUCTABLE_UPDATE_PERIOD				0.2
#define DESTRCUTABLE_ATTACKEDCLOCK				2
#define DESTRCUTABLE_EXPLOSIONSIZE_SMALL		0
#define DESTRCUTABLE_EXPLOSIONSIZE_MEDIUM		1
#define DESTRCUTABLE_EXPLOSIONSIZE_LARGE		2

class Weapon;

class Destructable : public DestructableData
{
public:
	// Constructor - Destructor
	Destructable(void);
	~Destructable(void);

	// Getters - Setters
	double getShield();
	void setShield(double p_shield);

	double getArmor();
	void setArmor(double p_armor);

	double getStructure();
	void setStructure(double p_structure);

	bool hasShield();
	bool hasArmor();
	bool hasStructure();

	bool isShieldChanged();
	bool isArmorChanged();
	bool isStructureChanged();

	bool isAttacked();
	void setAttacked(bool p_attacked);

	// Methods
	void incShield(double p_value);
	void decShield(double p_value);

	void incArmor(double p_value);
	void decArmor(double p_value);
	
	void incStructure(double p_value);
	void decStructure(double p_value);

	void notifyShieldChanged();
	void notifyShieldMaxChanged();
	void notifyArmorChanged();
	void notifyArmorMaxChanged();
	void notifyStructureChanged();
	void notifyStructureMaxChanged();

	void update();
	void heal(double p_heal);
	bool takeDamage(Weapon* p_weapon);
	virtual void destroy() = 0;


private:
	// Attributs
	double mShield;
	bool mShieldChanged;
	double mArmor;
	bool mArmorChanged;
	double mStructure;
	bool mStructureChanged;

	mks::Clock mClockRegen;
	mks::Clock mClockAttacked;
};

