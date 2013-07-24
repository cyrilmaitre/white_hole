#include "NpcShip.h"
#include "Camera.h"
#include "Wreck.h"
#include "WreckManager.h"
#include "Game.h"

//*************************************************************
// Define
//*************************************************************
#define TARGET_GEN_RANGE	1250


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
NpcShip::NpcShip( double p_spawnX, double p_spawnY ): Ship(p_spawnX, p_spawnY), NpcMovable(this)
{
	this->setSpawnX(p_spawnX);
	this->setSpawnY(p_spawnY);
	this->setTargetGenRange(TARGET_GEN_RANGE);
	this->setObjectType(MapObjectType::TypeNpcShip);
}

NpcShip::~NpcShip(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
double NpcShip::getSpawnX()
{
	return this->mSpawnX;
}

void NpcShip::setSpawnX( double p_spawnX )
{
	this->mSpawnX = p_spawnX;
	this->setX(p_spawnX);
	this->setSourceX(p_spawnX);
}

double NpcShip::getSpawnY()
{
	return this->mSpawnY;
}

void NpcShip::setSpawnY( double p_spawnY )
{
	this->mSpawnY = p_spawnY;
	this->setY(p_spawnY);
	this->setSourceY(p_spawnY);
}

NpcShipModel * NpcShip::getNpcShipModel()
{
	return this->mNpcShipModel;
}

void NpcShip::setNpcShipModel( NpcShipModel *p_model )
{
	this->mNpcShipModel = p_model;
	this->loadFromNpcShipModel();
}


//*************************************************************
// Methods
//*************************************************************
void NpcShip::draw()
{
	Ship::draw();
}

void NpcShip::update()
{
	Ship::update();
	NpcMovable::update();
}

void NpcShip::update(sf::Event p_event)
{
	Ship::update(p_event);
}

void NpcShip::loadFromNpcShipModel()
{
	this->setShipModel(this->getNpcShipModel()->getShipModel());
	this->loadNpcDataFromNpcData(this->getNpcShipModel());
}

void NpcShip::destroy()
{
	Entity::destroy();
	WreckManager::add(new Wreck(this));
	Game::game->getCharacter()->incExperience(this->generateLootExperience());
}


