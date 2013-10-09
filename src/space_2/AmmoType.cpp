#include "AmmoType.h"
#include "SplitString.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
AmmoType::AmmoType( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

AmmoType::~AmmoType(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long AmmoType::getIdAmmoType()
{
	return this->mIdAmmoType;
}

void AmmoType::setIdAmmoType( long p_id )
{
	this->mIdAmmoType = p_id;
}

std::string AmmoType::getName()
{
	return this->mName;
}

void AmmoType::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string AmmoType::getDescription()
{
	return this->mDescription;
}

void AmmoType::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

sf::Color AmmoType::getColor()
{
	return this->mColor;
}

void AmmoType::setColor( sf::Color p_color )
{
	this->mColor = p_color;
}

int AmmoType::getDamageShieldBonus()
{
	return this->mDamageBonus[0];
}

int AmmoType::getDamageShieldMalus()
{
	return this->mDamageMalus[0];
}

float AmmoType::getDamageShieldMultiplier()
{
	return 1.f + ((float)this->getDamageShieldBonus() - (float)this->getDamageShieldMalus()) / 100.f;
}

int AmmoType::getDamageArmorBonus()
{
	return this->mDamageBonus[1];
}

int AmmoType::getDamageArmorMalus()
{
	return this->mDamageMalus[1];
}

float AmmoType::getDamageArmorMultiplier()
{
	return 1.f + ((float)this->getDamageArmorBonus() - (float)this->getDamageArmorMalus()) / 100.f;
}

int AmmoType::getDamageStructureBonus()
{
	return this->mDamageBonus[2];
}

int AmmoType::getDamageStructureMalus()
{
	return this->mDamageMalus[2];
}

float AmmoType::getDamageStructureMultiplier()
{
	return 1.f + ((float)this->getDamageStructureBonus() - (float)this->getDamageStructureMalus()) / 100.f;
}

void AmmoType::setDamageBonus( std::string p_bonus )
{
	SplitString bonusValue(p_bonus, ";");
	this->mDamageBonus[0] = Tools::getIntFromString(bonusValue.getSplitString(0));
	this->mDamageBonus[1] = Tools::getIntFromString(bonusValue.getSplitString(1));
	this->mDamageBonus[2] = Tools::getIntFromString(bonusValue.getSplitString(2));
}

void AmmoType::setDamageMalus( std::string p_malus )
{
	SplitString malusValue(p_malus, ";");
	this->mDamageMalus[0] = Tools::getIntFromString(malusValue.getSplitString(0));
	this->mDamageMalus[1] = Tools::getIntFromString(malusValue.getSplitString(1));
	this->mDamageMalus[2] = Tools::getIntFromString(malusValue.getSplitString(2));
}


//*************************************************************
// Methods
//*************************************************************
void AmmoType::loadFromConfig( KeyValueFile* p_config )
{
	this->setIdAmmoType(p_config->getLong(AMMOTYPE_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(AMMOTYPE_CONFIG_NAME)));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(AMMOTYPE_CONFIG_DESCRIPTION)));
	this->setColor(ToolsImage::hexaToColor(p_config->getString(AMMOTYPE_CONFIG_COLOR)));
	this->setDamageBonus(p_config->getString(AMMOTYPE_CONFIG_DAMAGEBONUS));
	this->setDamageMalus(p_config->getString(AMMOTYPE_CONFIG_DAMAGEMALUS));
}






