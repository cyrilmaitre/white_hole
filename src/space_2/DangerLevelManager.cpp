#include "DangerLevelManager.h"
#include "FactoryGet.h"


//*************************************************************
// Init static
//*************************************************************
DangerLevelManager * DangerLevelManager::mInstance;


//*************************************************************
// Constructor - Destructor
//*************************************************************
DangerLevelManager::DangerLevelManager( KeyValueFile *p_config )
{
	this->setLevelMin(p_config->getInt("levelmin"));
	this->setLevelMax(p_config->getInt("levelmax"));
	this->setLevelCount(p_config->getInt("levelcount"));
	this->setLevelUpChanceMin(p_config->getFloat("levelupchancemin"));
	this->setLevelUpChanceMax(p_config->getFloat("levelupchancemax"));
}

DangerLevelManager::~DangerLevelManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
int DangerLevelManager::getLevelMin()
{
	return this->mLevelMin;
}

void DangerLevelManager::setLevelMin( int p_min )
{
	if(p_min < 0)
		p_min = 0;

	this->mLevelMin = p_min;
}

int DangerLevelManager::getLevelMed()
{
	return (this->getLevelMax() - this->getLevelMin()) / 2;
}

int DangerLevelManager::getLevelMax()
{
	return this->mLevelMax;
}

void DangerLevelManager::setLevelMax( int p_max )
{
	this->mLevelMax = p_max;
}

int DangerLevelManager::getLevelCount()
{
	return this->mLevelCount;
}

void DangerLevelManager::setLevelCount( int p_count )
{
	this->mLevelCount = p_count;
}

float DangerLevelManager::getLevelUpChanceMin()
{
	return this->mLevelUpChanceMin;
}

void DangerLevelManager::setLevelUpChanceMin( float p_min )
{
	if(p_min < 0)
		p_min = 0;
	else if(p_min > 1)
		p_min = 1;

	this->mLevelUpChanceMin = p_min;
}

float DangerLevelManager::getLevelUpChanceMax()
{
	return this->mLevelUpChanceMax;
}

void DangerLevelManager::setLevelUpChanceMax( float p_max )
{
	if(p_max < 0)
		p_max = 0;
	else if(p_max > 1)
		p_max = 1;

	this->mLevelUpChanceMax = p_max;
}


//*************************************************************
// Methods
//*************************************************************
DangerLevelManager * DangerLevelManager::getInstance()
{
	return DangerLevelManager::mInstance;
}

void DangerLevelManager::init()
{
	DangerLevelManager::mInstance = new DangerLevelManager(Resource::resource->getConfig("dangerlevel"));
}

void DangerLevelManager::uninit()
{
	delete DangerLevelManager::mInstance;
}

DangerLevel* DangerLevelManager::generateDangerLevel( int p_dangerLevelCount, int p_dangerLevelSum )
{
	int dangerLevelCount = p_dangerLevelCount;
	int dangerLevelSum = p_dangerLevelSum;
	int dangerLevelAverage = -1;

	// Case first generation
	if(dangerLevelCount == 0)
		return FactoryGet::getDangerLevelFactory()->getDangerLevel(this->getLevelMed());

	// Average of danger level
	if(Tools::randomBool())
		dangerLevelAverage = floor((float)dangerLevelSum / (float)dangerLevelCount);
	else
		dangerLevelAverage = ceil((float)dangerLevelSum / (float)dangerLevelCount);

	// Manage min / max
	if(dangerLevelAverage == this->getLevelMin())
		return FactoryGet::getDangerLevelFactory()->getDangerLevel(this->getLevelMin() + 1);
	else if(dangerLevelAverage == this->getLevelMax())
		return FactoryGet::getDangerLevelFactory()->getDangerLevel(this->getLevelMax() - 1);

	// Comptute percentage up
	float random = Tools::randomZeroToOne();
	float chanceUp = 1.f - ((float)dangerLevelAverage / (float)this->getLevelCount());

	// Check
	if(chanceUp < this->getLevelUpChanceMin())
		chanceUp = this->getLevelUpChanceMin();
	else if(chanceUp > this->getLevelUpChanceMax())
		chanceUp = this->getLevelUpChanceMax();
		
	// Return
	if(random < chanceUp)
		dangerLevelAverage++;
	else if(random > chanceUp)
		dangerLevelAverage--;

	if(dangerLevelAverage < this->getLevelMin())
		dangerLevelAverage = this->getLevelMin();
	else if(dangerLevelAverage > this->getLevelMax())
		dangerLevelAverage = this->getLevelMax();

	// Debug
	// return FactoryGet::getDangerLevelFactory()->getDangerLevel(dangerLevelAverage);
	return FactoryGet::getDangerLevelFactory()->getDangerLevel(10);
}




