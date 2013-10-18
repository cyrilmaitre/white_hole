#pragma once
#include "Item.h"


class WeaponModel: public Item
{
public:
	// Constructor - Destructor 
	WeaponModel(KeyValueFile* p_config);
	~WeaponModel(void);

	// Getters - Setters
	double getDamageMultiplier();
	void setDamageMultiplier(double p_multiplier);

	int getAmmoMax();
	void setAmmoMax(int p_max);

	double getRange();
	void setRange(double p_range);

	double getRangeAngle();
	void setRangeAngle(double p_angle);

	float getReloadingSpeed();
	void setReloadingSpeed(float p_speed);

	float getFireRate();
	void setFireRate(float p_fireRate);

	std::string getSoundReload();
	void setSoundReload(std::string p_sound);

	int getAmmoTypeAllowedCount();
	ItemType* getAmmoTypeAllowed(int p_index);
	std::vector<ItemType*> getAmmoTypeAllowed();
	bool isAmmoTypeAllowed(ItemType* p_type);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	double mDamageMultiplier;
	int mAmmoMax;
	double mRange;
	double mRangeAngle;
	float mReloadingSpeed;
	float mFireRate;
	std::string mSoundReload;

	std::vector<ItemType*> mAmmoTypeAllowed;
};



