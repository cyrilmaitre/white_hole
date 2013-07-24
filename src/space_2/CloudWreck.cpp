#include "CloudWreck.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define ROTATIONSPEED_MIN				1.f		// degree per sec	
#define ROTATIONSPEED_MAX				1.5		// degree per sec
#define ROTATIONDIRECTION_RIGHT			true
#define ROTATIONDIRECTION_LEFT			false


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudWreck::CloudWreck(void)
{
	this->mCloudModel = NULL;
	this->setPlane(MAPOBJECT_PLANE_18);
	this->setObjectType(MapObject::MapObjectType::TypeCloudWreck);
	this->setObjectOpacity(MapObjectOpacity::Opacity4);
	this->desactivateOverable();

	this->setRotationDirection(Tools::randomBool());
	this->setRotationSpeed(Tools::random(ROTATIONSPEED_MIN, ROTATIONSPEED_MAX));
}

CloudWreck::~CloudWreck(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
CloudWreckModel* CloudWreck::getCloudModel()
{
	return this->mCloudModel;
}

void CloudWreck::setCloudModel( CloudWreckModel* p_model )
{
	if(this->mCloudModel != p_model)
	{
		this->mCloudModel = p_model;
		this->notifyCloudModelChanged();
	}
}

float CloudWreck::getRotationSpeed()
{
	return this->mRotationSpeed;
}

void CloudWreck::setRotationSpeed( float p_speed )
{
	this->mRotationSpeed = p_speed;
}

bool CloudWreck::getRotationDirection()
{
	return this->mRotationDirection;
}

void CloudWreck::setRotationDirection( bool p_direction )
{
	this->mRotationDirection = p_direction;
}


//*************************************************************
// Methods
//*************************************************************
void CloudWreck::update()
{
	MapObject::update();

	float rotationDiff = this->mRotationClock.getElapsedTimeAsSeconds() * this->getRotationSpeed();
	this->mRotationClock.restart();
	if(this->getRotationDirection() == ROTATIONDIRECTION_RIGHT)
		this->setRotation(this->getRotation() + rotationDiff);
	else
		this->setRotation(this->getRotation() - rotationDiff);
}

void CloudWreck::notifyCloudModelChanged()
{
	if(this->getCloudModel() != NULL)
	{
		this->setScale(this->getCloudModel()->getRandomScale());
		this->setSize(this->getCloudModel()->getHitBoxWidth(), this->getCloudModel()->getHitBoxHeight());
		this->setObjectOpacity(this->getCloudModel()->getOpacity());
		this->loadSprite();
	}
}

void CloudWreck::notifyRotationChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setRotation(this->getRotation());
}

void CloudWreck::loadSprite()
{
	MapObject::loadSprite();

	if(this->getCloudModel() != NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(this->getCloudModel()->getSprite()));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
		this->mObjectSprite->setRotation(this->getRotation());
		this->mObjectSprite->setScale(this->mScale, this->mScale);

		this->updateSprite();
	}
}


