#pragma once
#include "NpcType.h"
#include "LootItemModel.h"
#include "Weapon.h"


class NpcData
{
public:
	// Constructor - Destructor
	NpcData(void);
	~NpcData(void);

	// Getters - Setters
	int getLevelMin();
	void setLevelMin(int p_min);

	int getLevelMax();
	void setLevelMax(int p_max);

	int getCharacterLevelMin();
	void setCharacterLevelMin(int p_min);

	int getCharacterLevelMax();
	void setCharacterLevelMax(int p_max);

	long getLootCreditMin();
	void setLootCreditMin(long p_min);

	long getLootCreditMax();
	void setLootCreditMax(long p_max);

	long getLootExperience();
	void setLootExperience(long p_experience);

	std::string getLootItemString();
	void setLootItemString(std::string p_loot);

	std::string getWeaponsString();
	void setWeaponsString(std::string p_weapons);

	double getAggroRange();
	void setAggroRange(double p_range);

	NpcType *getNpcType();
	void setNpcType(NpcType *p_type);

	// Methods
	int generateLevel();
	long generateLootExperience();
	long generateLootCredit();
	std::vector<LootItemModel*> generateLootItem();
	void loadWeaponsToEntity(Entity* p_entity);

	virtual void loadNpcDataFromConfig(KeyValueFile *p_config);
	virtual void loadNpcDataFromNpcData(NpcData* p_object);


private:
	// Attributs
	int mLevelMin;
	int mLevelMax;
	int mCharacterLevelMin;
	int mCharacterLevelMax;
	long mLootCreditMin;
	long mLootCreditMax;
	long mLootExperience;

	std::string mLootItemString;
	std::map<LootItemModel*, float> mLootItems;

	std::string mWeaponsString;	
	double mAggroRange;

	NpcType *mNpcType;
};

