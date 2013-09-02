#include "Wreck.h"
#include "ToolsImage.h"
#include "Game.h"
#include "ToolsMap.h"
#include "WreckMini.h"
#include "Tools.h"
#include "ExplosionEffect.h"
#include "EntityManager.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
#define WRECKMINI_DENSITY_REF		64	// px²
#define WRECKMINI_DENSITY_MIN		2	// Per 64px²
#define WRECKMINI_DENSITY_MAX		4	// Per 64 px²
#define WRECKMINI_TRIGGER			
#define ROTATION_VELOCITY_MIN		0.1
#define ROTATION_VELOCITY_MAX		0.5
#define EMBER_ALPHA_MIN				100
#define EMBER_ALPHA_MAX				255
#define EMBER_ALPHA_PROC_MIN		0.f		// sec
#define EMBER_ALPHA_PROC_MAX		4.f		// sec
#define EMBER_ALPHA_SPEED			60		// alpha per sec


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
	this->mEmberSprite = NULL;

	this->setRotationInfinite(true);
	this->setRotationInfiniteRight(Tools::randomBool());
	this->setRotationVelocity(Tools::random((float)ROTATION_VELOCITY_MIN, (float)ROTATION_VELOCITY_MAX));

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
	for(int i = 0; i < this->mWreckMini.size(); i++)
	{
		Game::game->getMap()->getMapObjectSelector()->removeMapObject(this->mWreckMini[i]);
		EntityManager::remove(this->mWreckMini[i]->getId());
	}

	if(Game::game->getUserInterface()->getWindowCargoLoot()->getWreck() == this)
	{
		Game::game->getUserInterface()->getWindowCargoLoot()->setWreck(NULL);
		Game::game->getUserInterface()->getWindowCargoLoot()->setOpen(false);
	}

	if(this->mEmberSprite != NULL)
		delete this->mEmberSprite;
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
	this->updateEmber();
	this->updateWreckMini();
}

void Wreck::updateEmber()
{
	if(this->mEmberAlphaState == EmberAlphaState::Stopped && this->mEmberAlphaTickClock.getElapsedTimeAsSeconds() > this->mEmberAlphaNextTick)
		this->mEmberAlphaState = EmberAlphaState::Down;

	if(this->mEmberAlphaState == EmberAlphaState::Up)
	{
		this->mEmberAlpha += this->mEmberAlphaClock.getElapsedTimeAsSeconds() * EMBER_ALPHA_SPEED;
		if(this->mEmberAlpha > EMBER_ALPHA_MAX)
		{
			this->mEmberAlpha = EMBER_ALPHA_MAX;
			this->mEmberAlphaState = EmberAlphaState::Stopped;
			this->mEmberAlphaTickClock.restart();
			this->computeEmberAlphaNextTick();
		}
	}
	else if(this->mEmberAlphaState == EmberAlphaState::Down)
	{
		this->mEmberAlpha -= this->mEmberAlphaClock.getElapsedTimeAsSeconds() * EMBER_ALPHA_SPEED;
		if(this->mEmberAlpha < EMBER_ALPHA_MIN)
		{
			this->mEmberAlpha = EMBER_ALPHA_MIN;
			this->mEmberAlphaState = EmberAlphaState::Up;
		}
	}

	if(this->mEmberSprite != NULL)
		this->mEmberSprite->setColor(sf::Color(255,255,255,this->mEmberAlpha));
	this->mEmberAlphaClock.restart();
}

void Wreck::updateSprite()
{
	Entity::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mEmberSprite != NULL)
		this->mEmberSprite->setPosition(objectPositionScreen.x, objectPositionScreen.y + this->getRocking());
}

void Wreck::update( sf::Event p_event )
{
	this->updateWreckMini(p_event);
	Entity::update(p_event);
}

void Wreck::updateWreckMini()
{
	for(int i = 0; i < this->mWreckMini.size(); i++)
	{
		this->mWreckMini[i]->update();

		if(this->mWreckMini[i]->isDestroy())
		{
			// Remove from other managers
			Game::game->getMap()->getMapObjectSelector()->removeMapObject(this->mWreckMini[i]);
			EntityManager::remove(this->mWreckMini[i]->getId());

			// Remove from this
			this->mWreckMini.erase(this->mWreckMini.begin() + i);

			// Stay on the same index
			i--;
		}
	}
}

void Wreck::updateWreckMini( sf::Event p_event )
{
	for(int i = 0; i < this->mWreckMini.size(); i++)
	{
		this->mWreckMini[i]->update(p_event);
	}	
}

void Wreck::draw()
{
	Entity::draw();

	if(this->isVisible())
	{
		if(this->mEmberSprite != NULL)
			Resource::resource->getApp()->draw(*this->mEmberSprite);
	}

	for(int i = 0; i < this->mWreckMini.size(); i++)
		this->mWreckMini[i]->draw();
}

void Wreck::loadSprite()
{
	Entity::loadSprite();

	this->setObjectSprite(this->getWreckSprite());
	this->mObjectSprite->setRotation(this->getRotation());

	if(this->mEmberSprite == NULL)
	{
		this->mEmberSprite = new sf::Sprite(*Resource::resource->getTexture(this->getWreckEmberSprite()));
		ToolsImage::setSpriteOriginCenter(this->mEmberSprite);

		this->computeEmberAlphaNextTick();
		this->mEmberAlpha = EMBER_ALPHA_MAX;
		this->mEmberAlphaState = EmberAlphaState::Stopped;
		this->mEmberSprite->setColor(sf::Color(255,255,255,this->mEmberAlpha));
	}

	this->updateSprite();
}

void Wreck::unloadSprite()
{
	Entity::unloadSprite();

	if(this->mEmberSprite != NULL)
	{
		delete this->mEmberSprite;
		this->mEmberSprite = NULL;
	}
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
	this->setWreckEmberSprite(p_entity->getWreckEmberSprite());

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

void Wreck::computeEmberAlphaNextTick()
{
	this->mEmberAlphaNextTick = Tools::random((float)EMBER_ALPHA_PROC_MIN, (float)EMBER_ALPHA_PROC_MAX);
}

void Wreck::notifyRotationChanged()
{
	Entity::notifyRotationChanged();

	if(this->mEmberSprite != NULL)
		this->mEmberSprite->setRotation(this->getRotation());
}









