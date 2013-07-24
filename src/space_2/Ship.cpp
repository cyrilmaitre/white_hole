#include "Ship.h"
#include "ToolsImage.h"
#include <math.h>

using namespace sf;
using namespace std;


//*************************************************************
// Constructor - Destructor
//*************************************************************
Ship::Ship( double p_x , double p_y ) : EntityMovable(p_x, p_y, SHIP_PLANE), mShipModel(NULL)
{
	this->mShipModel = NULL;
	this->setWeaponSlotMax(0);
	this->setUpgradeSlotMax(0);
	this->setStuffSlotMax(0);
	this->setObjectOpacity(MapObjectOpacity::Opacity0);
}

Ship::~Ship(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ShipModel * Ship::getShipModel()
{
	return this->mShipModel;
}

void Ship::setShipModel( ShipModel *p_shipModel )
{
	this->mShipModel = p_shipModel;
	this->loadFromShipModel();
}


//*************************************************************
// Method
//*************************************************************
void Ship::draw()
{
	EntityMovable::draw();
}

void Ship::update()
{
	EntityMovable::update();

	if(this->mClockFiring.getElapsedTimeAsMilliseconds() > SHIP_FIRING_CYCLE)
		this->mClockFiring.restart();
}

void Ship::update(sf::Event p_event)
{
	EntityMovable::update(p_event);	
}

void Ship::notifyRotationChanged()
{
	EntityMovable::notifyRotationChanged();
	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setRotation(this->getRotation());
}

void Ship::loadSprite()
{
	EntityMovable::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(this->getShipModel()->getSprite()));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
}

void Ship::loadFromShipModel()
{
	if(this->getShipModel() != NULL)
	{
		DestructableData::loadFromDestructableData(this->getShipModel());
		MovableData::loadFromMovableData(this->getShipModel());
		WeaponableData::loadFromWeaponableData(this->getShipModel());
		UpgradableData::loadFromUpgradableData(this->getShipModel());
		StuffableData::loadFromStuffableData(this->getShipModel());
		RotableData::loadFromRotableData(this->getShipModel());

		this->setScale(this->getShipModel()->getRandomScale());
		this->setSize(this->getShipModel()->getHitBoxWidth(), this->getShipModel()->getHitBoxHeight());
		this->loadSprite();
	}
}
