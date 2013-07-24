#include "MovableData.h"


//*************************************************************
// Define
//*************************************************************
#define CONFIG_VELOCITYMAX				"velocity"
#define CONFIG_QUICKENING				"quickening"
#define CONFIG_REACTORCOUNT				"reactor_count"
#define CONFIG_REACTORSIZE				"reactor_size"
#define CONFIG_REACTORPOSITION			"reactor_position"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MovableData::MovableData(void)
{
	this->mVelocityMax = 0;
	this->mQuickening = 0;
}

MovableData::~MovableData(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
float MovableData::getVelocityMax()
{
	return this->mVelocityMax;
}

void MovableData::setVelocityMax( float p_velocityMax )
{
	// Check param
	if(p_velocityMax < 0)
		p_velocityMax = 0;

	// Set
	this->mVelocityMax = p_velocityMax;
}

float MovableData::getQuickening()
{
	return this->mQuickening;
}

void MovableData::setQuickening( float p_quickening )
{
	this->mQuickening = p_quickening;
}

int MovableData::getReactorCount()
{
	return this->mReactorCount;
}

void MovableData::setReactorCount( int p_count )
{
	this->mReactorCount = p_count;
}

int MovableData::getReactorSize()
{
	return this->mReactorSize;
}

void MovableData::setReactorSize( int p_size )
{
	this->mReactorSize = p_size;
}

sf::Vector2i MovableData::getReactorPosition( int p_index )
{
	return this->mReactorPosition[p_index];
}


//*************************************************************
// Methods
//*************************************************************
void MovableData::loadFromConfig( KeyValueFile* p_config )
{
	if(p_config->has(CONFIG_VELOCITYMAX))
		this->setVelocityMax(p_config->getFloat(CONFIG_VELOCITYMAX));

	if(p_config->has(CONFIG_QUICKENING))
		this->setQuickening(p_config->getFloat(CONFIG_QUICKENING));

	if(p_config->has(CONFIG_REACTORCOUNT))
		this->setReactorCount(p_config->getInt(CONFIG_REACTORCOUNT));

	if(p_config->has(CONFIG_REACTORSIZE))
		this->setReactorSize(p_config->getInt(CONFIG_REACTORSIZE));

	if(p_config->has(CONFIG_REACTORPOSITION))
	{
		this->mReactorPositionJson = p_config->getString(CONFIG_REACTORPOSITION);
		this->processReactorPositionJson();
	}
}

void MovableData::loadFromMovableData( MovableData* p_object )
{
	this->setVelocityMax(p_object->getVelocityMax());
	this->setQuickening(p_object->getQuickening());
}

void MovableData::processReactorPositionJson()
{
	Json::Value jsonPosition;   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(this->mReactorPositionJson, jsonPosition);
	if(parsingSuccessfull)
	{
		for(int i = 0; i < this->getReactorCount(); i++)
		{
			Json::Value currentJsonPosition = jsonPosition.get(i, NULL);
			if(currentJsonPosition != NULL)
				this->mReactorPosition.push_back(sf::Vector2i(currentJsonPosition.get("x", 0).asInt(), currentJsonPosition.get("y", 0).asInt()));
		}
	}
}

