#include "StationModel.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_SPINNERSPRITE		"sprite_spinner"
#define CONFIG_SPINNERVELOCITY		"spinner_velocity"


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationModel::StationModel(KeyValueFile* p_config) : MapObjectModel(p_config)
{
	this->mSpinnerSprite = "";
	this->mSpinnerVelocity = 0;
	this->loadFromConfig(p_config);
}

StationModel::~StationModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string StationModel::getSpinnerSprite()
{
	return this->mSpinnerSprite;
}

void StationModel::setSpinnerSprite( std::string p_sprite )
{
	this->mSpinnerSprite = p_sprite;
}

float StationModel::getSpinnerVelocity()
{
	return this->mSpinnerVelocity;
}

void StationModel::setSpinnerVelocity( float p_velocity )
{
	this->mSpinnerVelocity = p_velocity;
}


//*************************************************************
// Methods
//*************************************************************
void StationModel::loadFromConfig( KeyValueFile* p_config )
{
	DestructableData::loadFromConfig(p_config);
	EquipableData::loadFromConfig(p_config);
	EntityData::loadFromConfig(p_config);
	NpcData::loadNpcDataFromConfig(p_config);

	if(p_config->has(CONFIG_SPINNERSPRITE))
		this->setSpinnerSprite(p_config->getString(CONFIG_SPINNERSPRITE));

	if(p_config->has(CONFIG_SPINNERVELOCITY))
		this->setSpinnerVelocity(p_config->getFloat(CONFIG_SPINNERVELOCITY));
}



