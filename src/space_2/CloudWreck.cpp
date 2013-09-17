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

	this->setRotationInfinite(true);
	this->setRotationInfiniteRight(Tools::randomBool());
	this->setRotationVelocity(Tools::random((float)ROTATIONSPEED_MIN, (float)ROTATIONSPEED_MAX));
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


//*************************************************************
// Methods
//*************************************************************
void CloudWreck::update()
{
	MapObject::update();
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


