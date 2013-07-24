#include "CloudGaz.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
CloudGaz::CloudGaz(void)
{
	this->mCloudModel = NULL;
	this->setPlane(MAPOBJECT_PLANE_17);
	this->setObjectType(MapObject::MapObjectType::TypeCloudGaz);
	this->setObjectOpacity(MapObjectOpacity::Opacity0);
	this->desactivateOverable();
}

CloudGaz::~CloudGaz(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
CloudGazModel* CloudGaz::getCloudModel()
{
	return this->mCloudModel;
}

void CloudGaz::setCloudModel( CloudGazModel* p_model )
{
	if(this->mCloudModel != p_model)
	{
		this->mCloudModel = p_model;
		this->notifyCloudModelChanged();
	}
}

sf::Color CloudGaz::getCloudColor()
{
	return this->mCloudColor;
}

void CloudGaz::setCloudColor( sf::Color p_color )
{
	if(this->mCloudColor != p_color)
	{
		this->mCloudColor = p_color;
		this->notifyCloudColorChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void CloudGaz::notifyCloudModelChanged()
{
	if(this->getCloudModel() != NULL)
	{
		this->setScale(this->getCloudModel()->getRandomScale());
		this->setSize(this->getCloudModel()->getHitBoxWidth(), this->getCloudModel()->getHitBoxHeight());
		this->loadSprite();
	}
}

void CloudGaz::notifyCloudColorChanged()
{
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setColor(this->mCloudColor);
}

void CloudGaz::loadSprite()
{
	MapObject::loadSprite();

	if(this->getCloudModel() != NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(this->getCloudModel()->getSprite()));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
		this->mObjectSprite->setRotation(this->getRotation());
		this->mObjectSprite->setScale(this->mScale, this->mScale);
		this->mObjectSprite->setColor(this->mCloudColor);

		this->updateSprite();
	}
}


