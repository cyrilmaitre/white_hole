#include "NpcData.h"
#include "FactoryGet.h"
#include "SplitString.h"
#include "IdValueFloat.h"
#include "IdValueLong.h"
#include "WeaponModel.h"
#include "FactoryGet.h"
#include "AmmoModel.h"


//*************************************************************
// Define
//*************************************************************
#define NPC_CONFIG_LEVELMIN				"levelmin"
#define NPC_CONFIG_LEVELMAX				"levelmax"
#define NPC_CONFIG_CHARACTERLEVELMIN	"characterlevelmin"	
#define NPC_CONFIG_CHARACTERLEVELMAX	"characterlevelmax"
#define NPC_CONFIG_LOOTCREDITMIN		"lootcreditmin"
#define NPC_CONFIG_LOOTCREDITMAX		"lootcreditmax"
#define NPC_CONFIG_EXPERIENCE			"lootexperience"
#define NPC_CONFIG_LOOTITEM				"lootitem"
#define NPC_CONFIG_NPCTYPE				"npctype"
#define NPC_CONFIG_AGGRORANGE			"aggrorange"
#define NPC_CONFIG_WEAPONS				"weapons"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
NpcData::NpcData(void)
{
	this->mLevelMin = 0;
	this->mLevelMax = 0;
	this->mCharacterLevelMin = 0;
	this->mCharacterLevelMax = 0;
	this->mLootCreditMin = 0;
	this->mLootCreditMax = 0;
	this->mLootExperience = 0;
	this->mAggroRange = 0;
	this->mLootItemString = "";
	this->mWeaponsString = "";
	this->mNpcType = NULL;
}

NpcData::~NpcData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int NpcData::getLevelMin()
{
	return this->mLevelMin;
}

void NpcData::setLevelMin( int p_min )
{
	this->mLevelMin = p_min;
}

int NpcData::getLevelMax()
{
	return this->mLevelMax;
}

void NpcData::setLevelMax( int p_max )
{
	this->mLevelMax = p_max;
}

int NpcData::getCharacterLevelMin()
{
	return this->mCharacterLevelMin;
}

void NpcData::setCharacterLevelMin( int p_min )
{
	this->mCharacterLevelMin = p_min;
}

int NpcData::getCharacterLevelMax()
{
	return this->mCharacterLevelMax;
}

void NpcData::setCharacterLevelMax( int p_max )
{
	this->mCharacterLevelMax = p_max;
}

long NpcData::getLootCreditMin()
{
	return this->mLootCreditMin;
}

void NpcData::setLootCreditMin( long p_min )
{
	this->mLootCreditMin = p_min;
}

long NpcData::getLootCreditMax()
{
	return this->mLootCreditMax;
}

void NpcData::setLootCreditMax( long p_max )
{
	this->mLootCreditMax = p_max;
}

long NpcData::getLootExperience()
{
	return this->mLootExperience;
}

void NpcData::setLootExperience( long p_experience )
{
	if(p_experience < 0)
		p_experience = 0;

	this->mLootExperience = p_experience;
}

std::string NpcData::getLootItemString()
{
	return this->mLootItemString;
}

void NpcData::setLootItemString( std::string p_loot )
{
	this->mLootItemString = p_loot;

	this->mLootItems.clear();
	SplitString lootItems(this->mLootItemString, ";");
	for(int i = 0; i < lootItems.getSplitCount(); i++)
	{
		IdValueFloat current(lootItems.getSplitString(i));
		this->mLootItems.insert(std::pair<LootItemModel*, float>(FactoryGet::getLootItemModelFactory()->getLootItemModel(current.getId()), current.getValue()));
	}
}

double NpcData::getAggroRange()
{
	return this->mAggroRange;
}

void NpcData::setAggroRange( double p_range )
{
	this->mAggroRange = p_range;
}

NpcType * NpcData::getNpcType()
{
	return this->mNpcType;
}

void NpcData::setNpcType( NpcType *p_type )
{
	if(this->mNpcType != p_type)
	{
		this->mNpcType = p_type;
		this->notifyNpcTypeChanged();
	}
}

std::string NpcData::getWeaponsString()
{
	return this->mWeaponsString;
}

void NpcData::setWeaponsString( std::string p_weapons )
{
	this->mWeaponsString = p_weapons;
}


//*************************************************************
// Methods
//*************************************************************
long NpcData::generateLootCredit()
{
	return Tools::random(this->getLootCreditMin(), this->getLootCreditMax());
}

long NpcData::generateLootExperience()
{
	return this->getLootExperience();
}

int NpcData::generateLevel()
{
	return 	Tools::random(this->getLevelMin(), this->getLevelMax());
}

std::vector<LootItemModel*> NpcData::generateLootItem()
{
	std::vector<LootItemModel*> listItem;

	std::map<LootItemModel*, float>::iterator iter;
	for (iter = this->mLootItems.begin(); iter != this->mLootItems.end(); ++iter) 
	{
		float random = Tools::randomZeroToOne();
		if(random <= iter->second)
		{
			listItem.push_back(iter->first);
		}
	}

	return listItem;
}

void NpcData::notifyNpcTypeChanged()
{

}

void NpcData::loadNpcDataFromConfig( KeyValueFile *p_config )
{
	if(p_config->has(NPC_CONFIG_LEVELMIN))
		this->setLevelMin(p_config->getInt(NPC_CONFIG_LEVELMIN));

	if(p_config->has(NPC_CONFIG_LEVELMAX))
		this->setLevelMax(p_config->getInt(NPC_CONFIG_LEVELMAX));

	if(p_config->has(NPC_CONFIG_CHARACTERLEVELMIN))
		this->setCharacterLevelMin(p_config->getInt(NPC_CONFIG_CHARACTERLEVELMIN));

	if(p_config->has(NPC_CONFIG_CHARACTERLEVELMAX))
		this->setCharacterLevelMax(p_config->getInt(NPC_CONFIG_CHARACTERLEVELMAX));

	if(p_config->has(NPC_CONFIG_LOOTCREDITMIN))
		this->setLootCreditMin(p_config->getLong(NPC_CONFIG_LOOTCREDITMIN));

	if(p_config->has(NPC_CONFIG_LOOTCREDITMAX))
		this->setLootCreditMax(p_config->getLong(NPC_CONFIG_LOOTCREDITMAX));

	if(p_config->has(NPC_CONFIG_EXPERIENCE))
		this->setLootExperience(p_config->getLong(NPC_CONFIG_EXPERIENCE));

	if(p_config->has(NPC_CONFIG_LOOTITEM))
		this->setLootItemString(p_config->getString(NPC_CONFIG_LOOTITEM));

	if(p_config->has(NPC_CONFIG_NPCTYPE))
		this->setNpcType(FactoryGet::getNpcTypeFactory()->getNpcType(p_config->getLong(NPC_CONFIG_NPCTYPE)));

	if(p_config->has(NPC_CONFIG_AGGRORANGE))
		this->setAggroRange(p_config->getDouble(NPC_CONFIG_AGGRORANGE));

	if(p_config->has(NPC_CONFIG_WEAPONS))
		this->setWeaponsString(p_config->getString(NPC_CONFIG_WEAPONS));
}

void NpcData::loadNpcDataFromNpcData( NpcData* p_object )
{
	this->setLevelMin(p_object->getLevelMin());
	this->setLevelMax(p_object->getLevelMax());
	this->setCharacterLevelMin(p_object->getCharacterLevelMin());
	this->setCharacterLevelMax(p_object->getCharacterLevelMax());
	this->setLootCreditMin(p_object->getLootCreditMin());
	this->setLootCreditMax(p_object->getLootCreditMax());
	this->setLootExperience(p_object->getLootExperience());
	this->setLootItemString(p_object->getLootItemString());
	this->setNpcType(p_object->getNpcType());
	this->setAggroRange(p_object->getAggroRange());
	this->setWeaponsString(p_object->getWeaponsString());
}

void NpcData::loadWeaponsToEntity( Entity* p_entity )
{
	if(this->getWeaponsString() != "" && p_entity != NULL)
	{
		SplitString weapons(this->mWeaponsString, ";");
		for(int i = 0; i < weapons.getSplitCount(); i++)
		{
			IdValueLong current(weapons.getSplitString(i));
			WeaponModel* currentWeaponModel = FactoryGet::getWeaponModelFactory()->getWeaponModel(current.getId());
			AmmoModel* currentAmmoModel = FactoryGet::getAmmoFactory()->getAmmo((int)current.getValue());
			if(currentWeaponModel != NULL && currentAmmoModel != NULL)
			{
				p_entity->addWeapon(new Weapon(p_entity, currentWeaponModel, currentAmmoModel));
			}
		}
	}
}	



