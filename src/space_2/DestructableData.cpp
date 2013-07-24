#include "DestructableData.h"


//*************************************************************
// Define
//*************************************************************
#define DESTRUCTABLEDATA_CONFIG_EXPLOSIONSIZE		"explosion_size"
#define DESTRUCTABLEDATA_CONFIG_WRECKSPRITE			"sprite_wreck"
#define CONFIG_SHIELDSPRITE							"sprite_shield"
#define DESTRUCTABLEDATA_CONFIG_SHIELD				"shield"
#define DESTRUCTABLEDATA_CONFIG_SHIELDREGEN			"shield_regen"
#define DESTRUCTABLEDATA_CONFIG_SHIELDRESIST		"shield_resist"
#define DESTRUCTABLEDATA_CONFIG_ARMOR				"armor"
#define DESTRUCTABLEDATA_CONFIG_ARMORREGEN			"armor_regen"
#define DESTRUCTABLEDATA_CONFIG_ARMORRESIST			"armor_resist"
#define DESTRUCTABLEDATA_CONFIG_STRUCTURE			"structure"
#define DESTRUCTABLEDATA_CONFIG_STRUCTUREREGEN		"structure_regen"
#define DESTRUCTABLEDATA_CONFIG_STRUCTURERESIST		"structure_resist"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
DestructableData::DestructableData(void)
{
	this->mExplosionSize = 1;
	this->mWreckSprite = "";
	this->mShieldSprite = "";
	this->mShieldMax = 0;
	this->mShieldRegen = 0;
	this->mShieldResist = 0;
	this->mShieldMaxChanged = false;
	this->mArmorMax = 0;
	this->mArmorRegen = 0;
	this->mArmorResist = 0;
	this->mArmorMaxChanged = false;
	this->mStructureMax = 0;
	this->mStructureRegen = 0;
	this->mStructureResist = 0;
	this->mStructureMaxChanged = false;
}

DestructableData::~DestructableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int DestructableData::getExplosionSize()
{
	return this->mExplosionSize;
}

void DestructableData::setExplosionSize( int p_size )
{
	this->mExplosionSize = p_size;
}

std::string DestructableData::getWreckSprite()
{
	return this->mWreckSprite;
}

void DestructableData::setWreckSprite( std::string p_sprite )
{
	this->mWreckSprite = p_sprite;
}

std::string DestructableData::getShieldSprite()
{
	return this->mShieldSprite;
}

void DestructableData::setShieldSprite( std::string p_sprite )
{
	this->mShieldSprite = p_sprite;
}

double DestructableData::getShieldMax()
{
	return this->mShieldMax;
}

void DestructableData::setShieldMax( double p_shieldMax )
{
	this->mShieldMax = p_shieldMax;
	this->notifyShieldMaxChanged();
}

double DestructableData::getShieldRegen()
{
	return this->mShieldRegen;
}

void DestructableData::setShieldRegen( double p_shieldRegen )
{
	this->mShieldRegen = p_shieldRegen;
}

double DestructableData::getShieldResist()
{
	return this->mShieldResist;
}

void DestructableData::setShieldResist( double p_shiedlResist )
{
	this->mShieldResist = p_shiedlResist;
}

double DestructableData::getArmorMax()
{
	return this->mArmorMax;
}

void DestructableData::setArmorMax( double p_armorMax )
{
	this->mArmorMax = p_armorMax;
	this->notifyArmorMaxChanged();
}

double DestructableData::getArmorRegen()
{
	return this->mArmorRegen;
}

void DestructableData::setArmorRegen( double p_armorRegen )
{
	this->mArmorRegen = p_armorRegen;
}

double DestructableData::getArmorResist()
{
	return this->mArmorResist;
}

void DestructableData::setArmorResist( double p_armorResist )
{
	this->mArmorResist = p_armorResist;
}

double DestructableData::getStructureMax()
{
	return this->mStructureMax;
}

void DestructableData::setStructureMax( double p_structureMax )
{
	this->mStructureMax = p_structureMax;
	this->notifyStructureMaxChanged();
}

double DestructableData::getStructureRegen()
{
	return this->mStructureRegen;
}

void DestructableData::setStructureRegen( double p_strctureRegen )
{
	this->mStructureRegen = p_strctureRegen;
}

double DestructableData::getStructureResist()
{
	return this->mStructureResist;
}

void DestructableData::setStructureResist( double p_structureResist )
{
	this->mStructureResist = p_structureResist;
}

bool DestructableData::isShieldMaxChanged()
{
	bool returnValue = this->mShieldMaxChanged;
	this->mShieldMaxChanged = false;
	return returnValue;
}

bool DestructableData::isArmorMaxChanged()
{
	bool returnValue = this->mArmorMaxChanged;
	this->mArmorMaxChanged = false;
	return returnValue;
}

bool DestructableData::isStructureMaxChanged()
{
	bool returnValue = this->mStructureMaxChanged;
	this->mStructureMaxChanged = false;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void DestructableData::notifyShieldMaxChanged()
{
	this->mShieldMaxChanged = true;
}

void DestructableData::notifyArmorMaxChanged()
{
	this->mArmorMaxChanged = true;
}

void DestructableData::notifyStructureMaxChanged()
{
	this->mStructureMaxChanged = true;
}

void DestructableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(DESTRUCTABLEDATA_CONFIG_EXPLOSIONSIZE))
		this->setExplosionSize(p_config->getInt(DESTRUCTABLEDATA_CONFIG_EXPLOSIONSIZE));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_WRECKSPRITE))
		this->setWreckSprite(p_config->getString(DESTRUCTABLEDATA_CONFIG_WRECKSPRITE));

	if(p_config->has(CONFIG_SHIELDSPRITE))
		this->setShieldSprite(p_config->getString(CONFIG_SHIELDSPRITE));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_SHIELD))
		this->setShieldMax(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_SHIELD));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_SHIELDREGEN))
		this->setShieldRegen(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_SHIELDREGEN));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_SHIELDRESIST))
		this->setShieldResist(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_SHIELDRESIST));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_ARMOR))
		this->setArmorMax(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_ARMOR));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_ARMORREGEN))
		this->setArmorRegen(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_ARMORREGEN));

	if(p_config->has(DESTRUCTABLEDATA_CONFIG_ARMORRESIST))
		this->setArmorResist(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_ARMORRESIST));
	
	if(p_config->has(DESTRUCTABLEDATA_CONFIG_STRUCTURE))
		this->setStructureMax(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_STRUCTURE));
	
	if(p_config->has(DESTRUCTABLEDATA_CONFIG_STRUCTUREREGEN))
		this->setStructureRegen(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_STRUCTUREREGEN));
	
	if(p_config->has(DESTRUCTABLEDATA_CONFIG_STRUCTURERESIST))
		this->setStructureResist(p_config->getDouble(DESTRUCTABLEDATA_CONFIG_STRUCTURERESIST));
}

void DestructableData::loadFromDestructableData( DestructableData* p_object )
{
	this->setExplosionSize(p_object->getExplosionSize());
	this->setShieldSprite(p_object->getShieldSprite());
	this->setWreckSprite(p_object->getWreckSprite());
	this->setShieldMax(p_object->getShieldMax());
	this->setShieldRegen(p_object->getShieldRegen());
	this->setShieldResist(p_object->getShieldResist());
	this->setArmorMax(p_object->getArmorMax());
	this->setArmorRegen(p_object->getArmorRegen());
	this->setArmorResist(p_object->getArmorResist());
	this->setStructureMax(p_object->getStructureMax());
	this->setStructureRegen(p_object->getStructureRegen());
	this->setStructureResist(p_object->getStructureResist());
}






