#include "TurretEffectModel.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_SPRITE				"sprite"
#define CONFIG_WEAPONPOSITION		"weapon_position"
#define JSON_POSITION_X				"x"
#define JSON_POSITION_Y				"y"


//*************************************************************
// Constructor - Destructor
//*************************************************************
TurretEffectModel::TurretEffectModel( KeyValueFile* p_config )
{
	this->loadFromConfig(p_config);
}

TurretEffectModel::~TurretEffectModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string TurretEffectModel::getSprite()
{
	return this->mSprite;
}

void TurretEffectModel::setSprite( std::string p_sprite )
{
	this->mSprite = p_sprite;
}

std::string TurretEffectModel::getWeaponPositionJson()
{
	return this->mWeaponPositionJson;
}

void TurretEffectModel::setWeaponPositionJson( std::string p_json )
{
	if(this->mWeaponPositionJson != p_json)
	{
		this->mWeaponPositionJson = p_json;
		this->notifyWeaponPositionJsonChanged();
	}
}

int TurretEffectModel::getWeaponPositionCount()
{
	return this->mWeaponPosition.size();
}

sf::Vector2f TurretEffectModel::getWeaponPosition( int p_index )
{
	return this->mWeaponPosition[p_index];
}


//*************************************************************
// Methods
//*************************************************************
void TurretEffectModel::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_SPRITE))
		this->setSprite(p_config->getString(CONFIG_SPRITE));

	if(p_config->has(CONFIG_WEAPONPOSITION))
		this->setWeaponPositionJson(p_config->getString(CONFIG_WEAPONPOSITION));
}

void TurretEffectModel::notifyWeaponPositionJsonChanged()
{
	Json::Value jsonPosition;   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(this->getWeaponPositionJson(), jsonPosition);
	if(parsingSuccessfull && jsonPosition.isArray())
	{
		for(int i = 0; i < jsonPosition.size(); i++)
		{
			Json::Value currentJson = jsonPosition.get(i, NULL);
			if(currentJson != NULL)
				this->mWeaponPosition.push_back(sf::Vector2f(currentJson.get(JSON_POSITION_X, 0).asFloat(), currentJson.get(JSON_POSITION_Y, 0).asFloat()));
		}
	}
}
