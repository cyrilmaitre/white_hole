#include "DangerLevel.h"
#include "SplitString.h"
#include "FactoryGet.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define DANGERLEVEL_CONFIG_ID						"id"
#define DANGERLEVEL_CONFIG_DANGERLEVEL				"dangerlevel"
#define DANGERLEVEL_CONFIG_DANGERLEVEL_COLOR		"dangerlevelcolor"
#define DANGERLEVEL_CONFIG_SHIPTYPE_SPAWN_COUNT		"shiptypespawncount"
#define DANGERLEVEL_CONFIG_SHIPTYPE_SPAWN_CHANCE	"shipmodelspawnchance"
#define DANGERLEVEL_CONFIG_PLANETCOUNT_MIN			"planetcountmin"
#define DANGERLEVEL_CONFIG_PLANETCOUNT_MAX			"planetcountmax"
#define DANGERLEVEL_CONFIG_CLOUDGAZCOUNT_MIN		"cloudgazcountmin"
#define DANGERLEVEL_CONFIG_CLOUDGAZCOUNT_MAX		"cloudgazcountmax"
#define DANGERLEVEL_CONFIG_CLOUDWRECKCOUNT_MIN		"cloudwreckcountmin"
#define DANGERLEVEL_CONFIG_CLOUDWRECKCOUNT_MAX		"cloudwreckcountmax"
#define CONFIG_STATIONCOUNT_MIN						"stationcountmin"
#define CONFIG_STATIONCOUNT_MAX						"stationcountmax"


//*************************************************************
// Constructor - Destructor
//*************************************************************
DangerLevel::DangerLevel( KeyValueFile *p_config )
{
	this->loadFromConfig(p_config);
	this->mShapeMapMini.setSize(sf::Vector2f(DANGERLEVEL_TEXTURE_MAPMINI_WIDTH, DANGERLEVEL_TEXTURE_MAPMINI_HEIGHT));
}

DangerLevel::~DangerLevel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
long DangerLevel::getIdDangerLevel()
{
	return this->mIdDangerLevel;
}

void DangerLevel::setIdDangerLevel( long p_id )
{
	this->mIdDangerLevel = p_id;
}

int DangerLevel::getDangerLevel()
{
	return this->mDangerLevel;
}

void DangerLevel::setDangerLevel( int p_level )
{
	this->mDangerLevel = p_level;
}

sf::Color DangerLevel::getDangerLevelColor()
{
	return this->mColor;
}

void DangerLevel::setDangerLevelColor( sf::Color p_color )
{
	this->mColor = p_color;
	this->mShapeMapMini.setFillColor(this->mColor);
}

int DangerLevel::getShipTypeSpawn( int p_index )
{
	return this->mShipTypeSpawn[p_index];
}

int DangerLevel::getShipTypeSpawnCount()
{
	return this->mShipTypeSpawn.size();
}

int DangerLevel::getShipTypeSpawnNumber( long p_shipTypeId )
{
	std::map<long, int>::iterator it;
	it = this->mShipTypeSpawnNumber.find(p_shipTypeId);

	if(it != this->mShipTypeSpawnNumber.end())
		return it->second;

	return -1;
}

void DangerLevel::getShipModelSpawnChanceByShipType( std::map<NpcShipModel*, float>& p_map, long p_shipTypeId )
{
	for(int i = 0; i < this->getShipModelSpawnCount(); i++)
	{
		NpcShipModel* currentModel = FactoryGet::getNpcShipModelFactory()->getNpcShipModel(this->mShipModelSpawn[i]);
		if(currentModel->getNpcType()->getIdNpcType() == p_shipTypeId)
		{
			p_map.insert(std::pair<NpcShipModel*, float>(currentModel, this->getShipModelSpawnChance(currentModel->getIdNpcShipModel())));
		}
	}
}

void DangerLevel::setShipTypeSpawnNumber( long p_shipTypeId, int p_count )
{
	bool isKeyExist = false;
	std::map<long, int>::iterator it;
	it = this->mShipTypeSpawnNumber.find(p_shipTypeId);

	if(it != this->mShipTypeSpawnNumber.end())
		isKeyExist = true;

	if(isKeyExist)
	{
		it->second = p_count;
	}
	else
	{
		this->mShipTypeSpawnNumber.insert(std::pair<long, int>(p_shipTypeId, p_count));
		this->mShipTypeSpawn.push_back(p_shipTypeId);
	}
}

void DangerLevel::setShipTypeSpawnNumber( std::string p_value )
{
	if(p_value != "NULL")
	{
		int startDelimeter = p_value.find("(");
		int endDemimeter = p_value.find(")");
		this->setShipTypeSpawnNumber(Tools::getLongFromString(p_value.substr(0, startDelimeter)), 
									Tools::getIntFromString(p_value.substr(startDelimeter+1, endDemimeter-startDelimeter-1)));
	}
}

int DangerLevel::getShipModelSpawn( int p_index )
{
	return this->mShipModelSpawn[p_index];
}

int DangerLevel::getShipModelSpawnCount()
{
	return this->mShipModelSpawn.size();
}

float DangerLevel::getShipModelSpawnChance( long p_shipModelId )
{
	std::map<long, float>::iterator it;
	it = this->mShipModelSpawnChance.find(p_shipModelId);

	if(it != this->mShipModelSpawnChance.end())
		return it->second;

	return -1;
}

void DangerLevel::setShipModelSpawnChance( long p_shipModelId, float p_chance )
{
	bool isKeyExist = false;
	std::map<long, float>::iterator it;
	it = this->mShipModelSpawnChance.find(p_shipModelId);

	if(it != this->mShipModelSpawnChance.end())
		isKeyExist = true;

	if(isKeyExist)
	{
		it->second = p_chance;
	}
	else
	{
		this->mShipModelSpawnChance.insert(std::pair<long, float>(p_shipModelId, p_chance));
		this->mShipModelSpawn.push_back(p_shipModelId);
	}
}

void DangerLevel::setShipModelSpawnChance( std::string p_value )
{
	if(p_value != "NULL")
	{
		int startDelimeter = p_value.find("(");
		int endDemimeter = p_value.find(")");
		this->setShipModelSpawnChance(Tools::getLongFromString(p_value.substr(0, startDelimeter)), 
									  Tools::getFloatFromString(p_value.substr(startDelimeter+1, endDemimeter-startDelimeter-1)));
	}
}

int DangerLevel::getPlanetCountMin()
{
	return this->mPlanetCountMin;
}

void DangerLevel::setPlanetCountMin( int p_min )
{
	this->mPlanetCountMin = p_min;
}

int DangerLevel::getPlanetCountMax()
{
	return this->mPlanetCountMax;
}

void DangerLevel::setPlanetCountMax( int p_max )
{
	this->mPlanetCountMax = p_max;
}

int DangerLevel::getCloudGazCountMin()
{
	return this->mCloudGazCountMin;
}

void DangerLevel::setCloudGazCountMin( int p_min )
{
	this->mCloudGazCountMin = p_min;
}

int DangerLevel::getCloudGazCountMax()
{
	return this->mCloudGazCountMax;
}

void DangerLevel::setCloudGazCountMax( int p_max )
{
	this->mCloudGazCountMax = p_max;
}

int DangerLevel::getCloudWreckCountMin()
{
	return this->mCloudWreckCountMin;
}

void DangerLevel::setCloudWreckCountMin( int p_min )
{
	this->mCloudWreckCountMin = p_min;
}

int DangerLevel::getCloudWreckCountMax()
{
	return this->mCloudWreckCountMax;
}

void DangerLevel::setCloudWreckCountMax( int p_max )
{
	this->mCloudWreckCountMax = p_max;
}

sf::RectangleShape* DangerLevel::getShapeMapMini()
{
	return &this->mShapeMapMini;
}

int DangerLevel::getStationCountMin()
{
	return this->mStationCountMin;
}

void DangerLevel::setStationCountMin( int p_min )
{
	this->mStationCountMin = p_min;
}

int DangerLevel::getStationCountMax()
{
	return this->mStationCountMax;
}

void DangerLevel::setStationCountMax( int p_max )
{
	this->mStationCountMax = p_max;
}


//*************************************************************
// Methods
//*************************************************************
int DangerLevel::generatePlanetCount()
{
	return Tools::random(this->getPlanetCountMin(), this->getPlanetCountMax());
}

int DangerLevel::generateCloudGazCount()
{
	return Tools::random(this->getCloudGazCountMin(), this->getCloudGazCountMax());
}

int DangerLevel::generateCloudWreckCount()
{
	return Tools::random(this->getCloudWreckCountMin(), this->getCloudWreckCountMax());
}

int DangerLevel::generateStationCount()
{
	return Tools::random(this->getStationCountMin(), this->getStationCountMax());
}

void DangerLevel::loadFromConfig( KeyValueFile *p_config )
{
	this->setIdDangerLevel(p_config->getLong(DANGERLEVEL_CONFIG_ID));
	this->setDangerLevel(p_config->getInt(DANGERLEVEL_CONFIG_DANGERLEVEL));
	this->setDangerLevelColor(ToolsImage::hexaToColor(p_config->getString(DANGERLEVEL_CONFIG_DANGERLEVEL_COLOR)));

	// ShipType count => id_shiptype(count);id_shiptype(count);id_shiptype(count)
	std::string shipTypeSpawnCount = p_config->getString(DANGERLEVEL_CONFIG_SHIPTYPE_SPAWN_COUNT);
	if(shipTypeSpawnCount != "NULL")
	{
		SplitString explodedString(shipTypeSpawnCount, ";");
		for(int i = 0; i < explodedString.getSplitCount(); i++)
			this->setShipTypeSpawnNumber(explodedString.getSplitString(i));
	}

	// ShipModel chance => id_shipmodel(chance);id_shipmodel(chance);id_shipmodel(chance)
	// Order is very important -> less chance to more chance	=> 0(0.2);1(0.5);5(0.9)
	std::string shipModelSpawnChance = p_config->getString(DANGERLEVEL_CONFIG_SHIPTYPE_SPAWN_CHANCE);
	if(shipModelSpawnChance != "NULL")
	{
		SplitString explodedString(shipModelSpawnChance, ";");
		for(int i = 0; i < explodedString.getSplitCount(); i++)
			this->setShipModelSpawnChance(explodedString.getSplitString(i));
	}

	this->setPlanetCountMin(p_config->getInt(DANGERLEVEL_CONFIG_PLANETCOUNT_MIN));
	this->setPlanetCountMax(p_config->getInt(DANGERLEVEL_CONFIG_PLANETCOUNT_MAX));
	this->setCloudGazCountMin(p_config->getInt(DANGERLEVEL_CONFIG_CLOUDGAZCOUNT_MIN));
	this->setCloudGazCountMax(p_config->getInt(DANGERLEVEL_CONFIG_CLOUDGAZCOUNT_MAX));
	this->setCloudWreckCountMin(p_config->getInt(DANGERLEVEL_CONFIG_CLOUDWRECKCOUNT_MIN));
	this->setCloudWreckCountMax(p_config->getInt(DANGERLEVEL_CONFIG_CLOUDWRECKCOUNT_MAX));
	this->setStationCountMin(p_config->getInt(CONFIG_STATIONCOUNT_MIN));
	this->setStationCountMax(p_config->getInt(CONFIG_STATIONCOUNT_MAX));
}



