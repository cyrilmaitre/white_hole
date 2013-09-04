#include "Station.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define ROTATION_VELOCITY_MIN		0.1
#define ROTATION_VELOCITY_MAX		0.5


//*************************************************************
// Constructor - Destructor
//*************************************************************
Station::Station(void) : Npc(this)
{
	this->mSpinnerSprite = NULL;
	this->mModel = NULL;
	this->setPlane(STATION_PLANE);
	this->setObjectType(MapObject::MapObjectType::TypeStation);

	this->setRotation(Tools::random(0, 360));
	this->setRotationInfinite(true);
	this->setRotationInfiniteRight(Tools::randomBool());
	this->setRotationVelocity(Tools::random((float)ROTATION_VELOCITY_MIN, (float)ROTATION_VELOCITY_MAX));
}

Station::~Station(void)
{
	if(this->mSpinnerSprite != NULL)
		delete this->mSpinnerSprite;
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

	this->updateSpinner();
}

void Station::updateSpinner()
{
	if(this->mSpinnerSprite != NULL)
	{
		this->mSpinnerRotation.update();
		this->mSpinnerSprite->setRotation(this->mSpinnerRotation.getRotation());
	}
}

void Station::updateSprite()
{
	Entity::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mSpinnerSprite != NULL)
		this->mSpinnerSprite->setPosition(objectPositionScreen.x, objectPositionScreen.y + this->getRocking());
}

void Station::draw()
{
	if(this->mSpinnerSprite != NULL)
		Resource::resource->getApp()->draw(*this->mSpinnerSprite);

	Entity::draw();
}

void Station::notifyModelChanged()
{
	if(this->getModel() != NULL)
	{
		WeaponableData::loadFromWeaponableData(this->getModel());
		DestructableData::loadFromDestructableData(this->getModel());
		EntityData::loadFromEntityData(this->getModel());
		this->loadNpcDataFromNpcData(this->getModel());

		this->mSpinnerRotation.setRotationVelocity(this->getModel()->getSpinnerVelocity());
		this->mSpinnerRotation.setRotationInfinite(true);
		this->mSpinnerRotation.setRotationInfiniteRight(Tools::randomBool());

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

		if(this->getModel()->getSpinnerSprite() != "")
		{
			this->mSpinnerSprite = new sf::Sprite(*Resource::resource->getTexture(this->getModel()->getSpinnerSprite()));
			ToolsImage::setSpriteOriginCenter(this->mSpinnerSprite);
			this->mSpinnerSprite->setScale(this->mScale, this->mScale);
			this->mSpinnerSprite->setRotation(this->getRotation());
		}

		this->updateSprite();
	}
}

void Station::unloadSprite()
{
	Entity::unloadSprite();

	if(this->mSpinnerSprite != NULL)
	{
		delete this->mSpinnerSprite;
		this->mSpinnerSprite = NULL;
	}
}

