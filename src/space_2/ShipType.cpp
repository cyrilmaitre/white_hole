#include "ShipType.h"
#include "ShipTypeFactory.h"
#include "ItemTierFactory.h"
#include "FactoryGet.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ShipType::ShipType( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

ShipType::~ShipType(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long ShipType::getId()
{
	return this->mId;
}

void ShipType::setId( long p_id )
{
	this->mId = p_id;
}

std::string ShipType::getName()
{
	return this->mName;
}

void ShipType::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string ShipType::getDescription()
{
	return this->mDescription;
}

void ShipType::setDescription(std::string p_descripion)
{
	this->mDescription = p_descripion;
}


//*************************************************************
// Getters - Setters
//*************************************************************
void ShipType::loadFromConfig( KeyValueFile* p_config )
{
	this->setId(p_config->getLong("id"));
	this->setName(Resource::resource->getBundle()->getString(p_config->getString("name")));
	this->setDescription(Resource::resource->getBundle()->getString(p_config->getString("description")));
}

