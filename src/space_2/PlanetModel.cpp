#include "PlanetModel.h"
#include "FactoryGet.h"
#include "SplitString.h"


//*************************************************************
// Define
//*************************************************************
#define PLANETMODEL_CONFIG_TEMPMIN			"tempmin"
#define PLANETMODEL_CONFIG_TEMPMAX			"tempmax"
#define PLANETMODEL_CONFIG_WEIGHTMIN		"weightmin"
#define PLANETMODEL_CONFIG_WEIGHTMAX		"weightmax"
#define PLANETMODEL_CONFIG_PLANES			"planes"
#define PLANETMODEL_CONFIG_PLANETTYPE		"planettype"


//*************************************************************
// Constructor - Destructor
//*************************************************************
PlanetModel::PlanetModel( KeyValueFile* p_config ) : MapObjectModel(p_config)
{
	this->loadFromConfig(p_config);
}

PlanetModel::~PlanetModel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float PlanetModel::getTempMin()
{
	return this->mTempMin;
}

void PlanetModel::setTempMin( float p_min )
{
	this->mTempMin = p_min;
}

float PlanetModel::getTempMax()
{
	return this->mTempMax;
}

void PlanetModel::setTempMax( float p_max )
{
	this->mTempMax = p_max;
}

float PlanetModel::getWeightMin()
{
	return this->mWeightMin;
}

void PlanetModel::setWeightMin( float p_min )
{
	this->mWeightMin = p_min;
}

float PlanetModel::getWeightMax()
{
	return this->mWeightMax;
}

void PlanetModel::setWeightMax( float p_max )
{
	this->mWeightMax = p_max;
}

std::string PlanetModel::getPlanes()
{
	return this->mPlanes;
}

void PlanetModel::setPlanes( std::string p_plane )
{
	this->mPlanes = p_plane;
}

PlanetType* PlanetModel::getPlanetType()
{
	return this->mPlanetType;
}

void PlanetModel::setPlanetType( PlanetType* p_type )
{
	this->mPlanetType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void PlanetModel::loadFromConfig( KeyValueFile* p_config )
{
	this->setWeightMin(p_config->getFloat(PLANETMODEL_CONFIG_WEIGHTMIN));
	this->setWeightMax(p_config->getFloat(PLANETMODEL_CONFIG_WEIGHTMAX));
	this->setTempMin(p_config->getFloat(PLANETMODEL_CONFIG_TEMPMIN));
	this->setTempMax(p_config->getFloat(PLANETMODEL_CONFIG_TEMPMAX));
	this->setPlanes(p_config->getString(PLANETMODEL_CONFIG_PLANES));
	this->setPlanetType(FactoryGet::getPlanetTypeFactory()->getPlanetType(p_config->getInt(PLANETMODEL_CONFIG_PLANETTYPE)));
}

float PlanetModel::getRandomTemp()
{
	return Tools::random(this->getWeightMin(), this->getWeightMax());
}

float PlanetModel::getRandomWeight()
{
	return Tools::random(this->getTempMin(), this->getTempMax());
}

int PlanetModel::getRandomPlane()
{
	SplitString planes(this->getPlanes(), ";");
	int randomValue = Tools::random(0, planes.getSplitCount());
	return Tools::getIntFromString(planes.getSplitString(randomValue));
}
