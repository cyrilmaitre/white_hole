#include "Wreck.h"
#include "ToolsImage.h"
#include "Game.h"
#include "ToolsMap.h"
#include "WreckMini.h"
#include "Tools.h"
#include "ExplosionEffect.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
#define WRECKMINI_DENSITY_REF		64	// px²
#define WRECKMINI_DENSITY_MIN		2	// Per 64px²
#define WRECKMINI_DENSITY_MAX		4	// Per 64 px²
#define WRECKMINI_TRIGGER			


//*************************************************************
// Constructor - Destructor
//*************************************************************
Wreck::Wreck( Entity* p_entity )
{
	this->init();

	if(p_entity->getObjectType() == MapObjectType::TypeNpcShip)
		this->loadFromNpcShip((NpcShip*)p_entity);
	else if(p_entity->getObjectType() == MapObjectType::TypeStation)
		this->loadFromStation((Station*)p_entity);
	else if(p_entity->getObjectType() != MapObjectType::TypeWreck)
		this->loadFromEntity(p_entity);

	this->mWreckMiniTriggered = false;
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

	for(int i = 0; i < this->mWreckMini.size(); i++)
		delete this->mWreckMini[i];
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
void Wreck::update()
{
	Entity::update();

	if(this->mWreckMiniClock.getElapsedTimeAsSeconds() > SHOCKWAVE_PHASE_BEGIN && !this->mWreckMiniTriggered)
	{
		int area = ceil((float)this->getRadius() / WRECKMINI_DENSITY_REF);
		int numberOfWreckMini = Tools::random(area * WRECKMINI_DENSITY_MIN, area * WRECKMINI_DENSITY_MAX);
		for(int i = 0; i < numberOfWreckMini; i++)
			this->mWreckMini.push_back(new WreckMini(this));
		this->mWreckMiniTriggered = true;
	}
	this->updateWreckMini();
}

void Wreck::update( sf::Event p_event )
{
	Entity::update(p_event);
}

void Wreck::updateWreckMini()
{
	for(int i = 0; i < this->mWreckMini.size(); i++)
		this->mWreckMini[i]->update();
}

void Wreck::draw()
{
	Entity::draw();

	for(int i = 0; i < this->mWreckMini.size(); i++)
		this->mWreckMini[i]->draw();
}

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

void Wreck::loadFromNpcShip( NpcShip* p_npcShip )
{
	this->setName(p_npcShip->getNpcShipModel()->getName());

	this->loadFromNpc(p_npcShip);
	this->loadFromEntity(p_npcShip);
}

void Wreck::loadFromStation( Station* p_station )
{
	this->setName(p_station->getObjectTypeName() + " " + Resource::resource->getBundle()->getString("wreck"));

	this->loadFromNpc(p_station);
	this->loadFromEntity(p_station);
}







