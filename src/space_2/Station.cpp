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
	Npc::update();
}

void Station::notifyModelChanged()
{
	if(this->getModel() != NULL)
	{
		WeaponableData::loadFromWeaponableData(this->getModel());
		DestructableData::loadFromDestructableData(this->getModel());
		EntityData::loadFromEntityData(this->getModel());
		this->loadNpcDataFromNpcData(this->getModel());

		this->setScale(this->getModel()->getRandomScale());
		this->setSize(this->getModel()->getHitBoxWidth(), this->getModel()->getHitBoxHeight());
		this->loadSprite();
	}
}

void Station::loadSprite()
{
	Entity::loadSprite();
	if(this->getModel() != NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(this->getModel()->getSprite()));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
		this->mObjectSprite->setScale(this->mScale, this->mScale);
		this->mObjectSprite->setRotation(this->getRotation());

		this->updateSprite();
	}
}
