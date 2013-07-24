#include "Wreck.h"
#include "ToolsImage.h"
#include "Game.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Wreck::Wreck( NpcShip* p_npcShip )
{
	this->init();
	this->loadFromNpcShip(p_npcShip);
}

void Wreck::init()
{
	this->setShieldMax(WRECK_SHIELD);
	this->setArmorMax(WRECK_ARMOR);
	this->setStructureMax(WRECK_STRUCTURE);
	this->setCargoMax(WRECK_CARGOMAX);
	this->setObjectType(MapObject::MapObjectType::TypeWreck);
	this->setObjectOpacity(MapObjectOpacity::Opacity7);
	this->mObjectClock.restart();
}

Wreck::~Wreck(void)
{
	if(Game::game->getUserInterface()->getWindowCargoLoot()->getWreck() == this)
	{
		Game::game->getUserInterface()->getWindowCargoLoot()->setWreck(NULL);
		Game::game->getUserInterface()->getWindowCargoLoot()->setOpen(false);
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string Wreck::getName()
{
	return this->mName;
}

void Wreck::setName( std::string p_name )
{
	this->mName = p_name;
}

long Wreck::getCredit()
{
	return this->mCredit;
}

void Wreck::setCredit( long p_credit )
{
	this->mCredit = p_credit;
}

bool Wreck::isOutOfDate()
{
	return this->mObjectClock.getElapsedTimeAsSeconds() > WRECK_OUTOFTIME;
}


//*************************************************************
// Methods
//*************************************************************
void Wreck::loadSprite()
{
	MapObject::loadSprite();
	this->setObjectSprite(this->getWreckSprite());
	this->mObjectSprite->setRotation(this->getRotation());
	this->updateSprite();
}

void Wreck::loadFromNpc( Npc* p_npc )
{
	this->setCredit(p_npc->generateLootCredit());

	std::vector<LootItemModel*> lootItems = p_npc->generateLootItem();
	for(int i = 0; i < lootItems.size(); i++)
	{
		this->addItemStack(new ItemStack(lootItems[i]));
	}
}

void Wreck::loadFromNpcShip( NpcShip* p_npcShip )
{
	this->setName(p_npcShip->getNpcShipModel()->getName());

	this->loadFromNpc(p_npcShip);
	this->loadFromEntity(p_npcShip);
}

void Wreck::loadFromEntity( Entity* p_entity )
{
	this->setX(p_entity->Object::getX());
	this->setY(p_entity->Object::getY());
	this->setWidth(p_entity->Object::getWidth());
	this->setHeight(p_entity->Object::getHeight());

	this->setRotation(p_entity->getRotation());
	this->setWreckSprite(p_entity->getWreckSprite());

	this->loadSprite();
}



