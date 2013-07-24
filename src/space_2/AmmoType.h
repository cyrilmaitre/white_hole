#pragma once
#include "Resource.h"
#include "KeyValueFile.h"

// Define
#define AMMOTYPE_CONFIG_ID				"id"
#define AMMOTYPE_CONFIG_NAME			"name"
#define AMMOTYPE_CONFIG_DESCRIPTION		"description"
#define AMMOTYPE_CONFIG_COLOR			"color"
#define AMMOTYPE_CONFIG_DAMAGEBONUS		"damagebonus"
#define AMMOTYPE_CONFIG_DAMAGEMALUS		"damagemalus"

#define AMMOTYPE_BONUS_COUNT	3
#define AMMOTYPE_MALUS_COUNT	3

class AmmoType
{
public:
	// Constructor - Destructor
	AmmoType(KeyValueFile* p_config);
	~AmmoType(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	std::string getName();
	void setName(std::string p_name);

	std::string getDescription();
	void setDescription(std::string p_description);

	std::string getColor();
	void setColor(std::string p_color);

	int getDamageShieldBonus();
	int getDamageShieldMalus();
	float getDamageShieldMultiplier();
	int getDamageArmorBonus();
	int getDamageArmorMalus();
	float getDamageArmorMultiplier();
	int getDamageStructureBonus();
	int getDamageStructureMalus();
	float getDamageStructureMultiplier();
	void setDamageBonus(std::string p_bonus);
	void setDamageMalus(std::string p_malus);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mId;
	std::string mName;
	std::string mDescription;
	std::string mColor;
	int mDamageBonus[AMMOTYPE_BONUS_COUNT];
	int mDamageMalus[AMMOTYPE_MALUS_COUNT];
};

