#include "Station.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define STATION_PLANE	MAPOBJECT_PLANE_1


//*************************************************************
// Constructor - Destructor
//*************************************************************
Station::Station(void) : Npc(this)
{
	this->mModel = NULL;
	this->setPlane(STATION_PLANE);
	this->setObjectType(MapObject::MapObjectType::TypeStation);
}

Station::~Station(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
StationModel* Station::getModel()
{
	return this->mModel;
}

void Station::setModel( StationModel* p_model )
{
	if(this->mModel != p_model)
	{
		this->mModel = p_model;
		this->notifyModelChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void Station::update()
{
	Entity::update();
	//Npc::update();	// Not necessary (cannot attak)
}

void Station::notifyModelChanged()
{
	if(this->getModel() != NULL)
	{
		DestructableData::loadFromDestructableData(this->getModel());
		NpcData::loadNpcDataFromNpcData(this->getModel());

		this->setWidth(this->getModel()->getWidth());
		this->setHeight(this->getModel()->getHeight());
		this->loadSprite();
	}
}

void Station::notifySizeChanged()
{
	Entity::notifySizeChanged();
	if(this->mObjectSprite != NULL)
		ToolsImage::resizeSprite(this->mObjectSprite, this->Object::getWidth(), this->Object::getHeight());
}

void Station::loadSprite()
{
	Entity::loadSprite();
	if(this->getModel() != NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(this->getModel()->getSprite()));
		this->mObjectSprite->setOrigin(this->mObjectSprite->getLocalBounds().width / 2, this->mObjectSprite->getLocalBounds().height / 2);
		ToolsImage::resizeSprite(this->mObjectSprite, this->Object::getWidth(), this->Object::getHeight());
		this->mObjectSprite->setRotation(this->getRotation());
		this->updateSprite();
	}
}
