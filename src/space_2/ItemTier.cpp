#include "ItemTier.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_ID				"id"
#define CONFIG_NAME				"name"
#define CONFIG_DESCRIPTION		"description"
#define CONFIG_COLOR			"color"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ItemTier::ItemTier( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

ItemTier::~ItemTier(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long ItemTier::getId()
{
	return this->mId;
}

void ItemTier::setId(long p_id)
{
	this->mId = p_id;
}

std::string ItemTier::getName()
{
	return this->mName;
}

void ItemTier::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string ItemTier::getDescription()
{
	return this->mDescription;
}

void ItemTier::setDescription( std::string p_description )
{
	this->mDescription = p_description;
}

std::string ItemTier::getColorString()
{
	return this->mColorString;
}

void ItemTier::setColorString( std::string p_color )
{
	this->mColorString = p_color;
	this->setColor(ToolsImage::hexaToColor(this->mColorString));
}

sf::Color ItemTier::getColor()
{
	return this->mColor;
}

void ItemTier::setColor( sf::Color p_color )
{
	this->mColor = p_color;
}


//*************************************************************
// Methode
//*************************************************************
void ItemTier::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_ID))
		this->setId(p_config->getLong(CONFIG_ID));

	if(p_config->has(CONFIG_NAME))
		this->setName(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_NAME)));

	if(p_config->has(CONFIG_DESCRIPTION))
		this->setDescription(Resource::resource->getBundle()->getString(p_config->getString(CONFIG_DESCRIPTION)));

	if(p_config->has(CONFIG_COLOR))
		this->setColorString(p_config->getString(CONFIG_COLOR));
}


