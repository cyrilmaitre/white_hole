#include "NpcType.h"
#include "ToolsImage.h"


//*************************************************************
// Define			
//*************************************************************
#define NPCTYPE_CONFIG_ID				"id"
#define NPCTYPE_CONFIG_NAME				"name"
#define NPCTYPE_CONFIG_COLOR			"color"
#define CONFIG_LIGHTCOLOR				"lightcolor"
#define NPCTYPE_CONFIG_ALIGNMENT		"alignment"
#define NPCTYPE_CONFIG_AGGRO			"aggro"


//*************************************************************
// Constructor - Destructor
//*************************************************************
NpcType::NpcType( KeyValueFile *p_config )
{
	this->loadFromConfig(p_config);
}

NpcType::~NpcType(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long NpcType::getIdNpcType()
{
	return this->mIdNpcType;
}

void NpcType::setIdNpcType( long p_id )
{
	this->mIdNpcType = p_id;
}

std::string NpcType::getName()
{
	return this->mName;
}

void NpcType::setName( std::string p_name )
{
	this->mName = p_name;
}

sf::Color NpcType::getColor()
{
	return this->mColor;
}

void NpcType::setColor( sf::Color p_color )
{
	this->mColor = p_color;
}

std::string NpcType::getColorString()
{
	return this->mColorString;
}

void NpcType::setColorString( std::string p_color )
{
	this->mColorString = p_color;
	this->setColor(ToolsImage::hexaToColor(this->mColorString));
}

FlashingLightEffect::LightColor NpcType::getLightColor()
{
	return this->mLightColor;
}

void NpcType::setLightColor( FlashingLightEffect::LightColor p_color )
{
	this->mLightColor = p_color;
}

NpcType::NpcTypeAlignment NpcType::getAlignment()
{
	return this->mAlignment;
}

void NpcType::setAlignment( NpcTypeAlignment p_alignment )
{
	this->mAlignment = p_alignment;
}

NpcType::NpcTypeAggro NpcType::getAggro()
{
	return this->mAggro;
}

void NpcType::setAggro( NpcTypeAggro p_aggro )
{
	this->mAggro = p_aggro;
}

bool NpcType::canAggro( NpcType* p_type )
{
	if(this->getAggro() != NpcTypeAggro::AggroAggressive)
		return false;
	
	if( (this->getAlignment() == NpcTypeAlignment::AlignmenGood && p_type->getAlignment() == NpcTypeAlignment::AlignmenEvil) ||
		(this->getAlignment() == NpcTypeAlignment::AlignmenEvil && (p_type->getAlignment() == NpcTypeAlignment::AlignmenGood || p_type->getAlignment() == NpcTypeAlignment::AlignmenNeutral)) ||
		(this->getAlignment() == NpcTypeAlignment::AlignmenNeutral && p_type->getAlignment() == NpcTypeAlignment::AlignmenNeutral))
		return true;

	return false;
}

bool NpcType::canRespond( NpcType* p_type )
{
	return this->getAggro() != NpcTypeAggro::AggroPassive && this->getAlignment() != p_type->getAlignment();
}

bool NpcType::isAgressive()
{
	return this->getAggro() == NpcTypeAggro::AggroAggressive;
}

bool NpcType::isPassive()
{
	return this->getAggro() == NpcTypeAggro::AggroPassive;
}


//*************************************************************
// Methods
//*************************************************************
void NpcType::loadFromConfig( KeyValueFile *p_config )
{
	this->setIdNpcType(p_config->getLong(NPCTYPE_CONFIG_ID));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString(NPCTYPE_CONFIG_NAME)));
	this->setColorString(p_config->getString(NPCTYPE_CONFIG_COLOR));
	this->setLightColor((FlashingLightEffect::LightColor)p_config->getInt(CONFIG_LIGHTCOLOR));
	this->setAlignment(NpcTypeAlignment(p_config->getInt(NPCTYPE_CONFIG_ALIGNMENT)));
	this->setAggro(NpcTypeAggro(p_config->getInt(NPCTYPE_CONFIG_AGGRO)));
}





