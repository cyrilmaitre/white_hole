#include "Entity.h"
#include "SpriteParameterFactory.h"
#include "Camera.h"
#include "ToolsImage.h"
#include "Game.h"
#include "AutoManager.h"
#include "ExplosionEffect.h"
#include "FlashingLightEffect.h"


//*************************************************************
// Define
//*************************************************************
#define CIRCLE_SELECTED_SIZE			100
#define SHIELDIMPACT_ALPHA				100
#define SHIELDIMPACT_ALPHARECOVER		50 // per sec


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Entity::Entity( int p_plane ) : MapObject(p_plane)
{
	this->mShieldSprite = NULL;
	this->mTBDistance.setFontColor(ENTITY_DISTANCE_FONT_COLOR);
	this->mTBDistance.setFontSize(ENTITY_DISTANCE_FONT_SIZE);
	this->mTBDistance.setText(Tools::buildStringWithInt(0) + Resource::resource->getBundle()->getString("meterAb"));
}

Entity::~Entity(void)
{
	if(this->mShieldSprite != NULL)
		delete this->mShieldSprite;
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityTarget* Entity::getTarget()
{
	return &this->mTarget;
}

bool Entity::isDestroy()
{
	return !this->hasStructure();
}


//*************************************************************
// Methods
//*************************************************************
void Entity::update()
{
	MapObject::update();
	Destructable::update();
	Rockable::update();
	Weaponable::update();

	this->updateShieldSprite();
	if(this->isSelected())
	{	
		sf::Vector2f objectPositionScreen = this->getScreenPosition();
		this->mTBDistance.setText(Tools::buildStringWithInt(Game::game->getMap()->getMapObjectSelector()->getObjectSelectedDistance()) + " " + Resource::resource->getBundle()->getString("meterAb"));
		this->mTBDistance.setX(objectPositionScreen.x - this->mTBDistance.getWidth() / 2);
		this->mTBDistance.setY(objectPositionScreen.y + CIRCLE_SELECTED_SIZE / 2 + this->getRocking() + ENTITY_DISTANCE_OFFSETY);
	}

	for(int i = 0; i < this->mRadars.size(); i++)
		this->mRadars[i]->update();

	for(int i = 0; i < this->mFlashingLights.size(); i++)
		this->mFlashingLights[i]->update();

	for(int i = 0; i < this->mTurrets.size(); i++)
		this->mTurrets[i]->update();
}

void Entity::updateShieldSprite()
{
	if(this->mShieldSprite != NULL)
	{
		int colorAlpha = this->mShieldSprite->getColor().a; 
		if(colorAlpha < 255)
		{
			colorAlpha += SHIELDIMPACT_ALPHARECOVER * this->mShieldClock.getElapsedTimeAsSeconds();
			if(colorAlpha > 255)
				colorAlpha = 255;
			this->mShieldSprite->setColor(sf::Color(255, 255, 255, colorAlpha));
		}
	}
}

void Entity::updateSprite()
{
	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mObjectSpriteParameter != NULL)
		this->mObjectSpriteParameter->getSprite().setPosition(objectPositionScreen.x, objectPositionScreen.y + this->getRocking());

	if(this->mObjectSprite != NULL)
		this->mObjectSprite->setPosition(objectPositionScreen.x, objectPositionScreen.y + this->getRocking());

	if(this->mShieldSprite != NULL)
		this->mShieldSprite->setPosition(objectPositionScreen.x, objectPositionScreen.y + this->getRocking());
}

void Entity::update( sf::Event p_event )
{
	MapObject::update(p_event);
}

void Entity::loadSprite()
{
	MapObject::loadSprite();

	if(this->getShieldSprite() != "")
	{
		this->mShieldSprite = new sf::Sprite(*Resource::resource->getTexture(this->getShieldSprite()));
		ToolsImage::setSpriteOriginCenter(this->mShieldSprite);
	}
}

void Entity::unloadSprite()
{
	MapObject::unloadSprite();

	if(this->mShieldSprite != NULL)
	{
		delete this->mShieldSprite;
		this->mShieldSprite = NULL;
	}
}

void Entity::notifyRotationChanged()
{
	if(this->mShieldSprite != NULL)
		this->mShieldSprite->setRotation(this->getRotation());
}

void Entity::notifyFlashingLightJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mFlashingLights.size(); i++)
		delete this->mFlashingLights[i];
	this->mFlashingLights.clear();

	// Add
	Json::Value jsonFlashingLight;   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(this->getFlashingLightJson(), jsonFlashingLight);
	if(parsingSuccessfull && jsonFlashingLight.isArray())
	{
		for(int i = 0; i < jsonFlashingLight.size(); i++)
		{
			Json::Value currentJson = jsonFlashingLight.get(i, NULL);
			if(currentJson != NULL)
				this->mFlashingLights.push_back(new FlashingLightEffect(this, currentJson));
		}
	}
}

void Entity::notifyRadarJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mRadars.size(); i++)
		delete this->mRadars[i];
	this->mRadars.clear();

	// Add
	Json::Value jsonRadar;   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(this->getRadarJson(), jsonRadar);
	if(parsingSuccessfull && jsonRadar.isArray())
	{
		for(int i = 0; i < jsonRadar.size(); i++)
		{
			Json::Value currentJson = jsonRadar.get(i, NULL);
			if(currentJson != NULL)
				this->mRadars.push_back(new RadarEffect(this, currentJson));
		}
	}
}

void Entity::notifyTurretJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mTurrets.size(); i++)
		delete this->mTurrets[i];
	this->mTurrets.clear();

	// Add
	Json::Value jsonTurret;   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(this->getTurretJson(), jsonTurret);
	if(parsingSuccessfull && jsonTurret.isArray())
	{
		for(int i = 0; i < jsonTurret.size(); i++)
		{
			Json::Value currentJson = jsonTurret.get(i, NULL);
			if(currentJson != NULL)
				this->mTurrets.push_back(new TurretEffect(this, currentJson));
		}
	}
}

void Entity::draw()
{
	if(this->isVisible())
	{
		if(this->mShieldSprite != NULL && this->hasShield())
			Resource::resource->getApp()->draw(*this->mShieldSprite);
	}

	MapObject::draw();

	for(int i = 0; i < this->mRadars.size(); i++)
		this->mRadars[i]->draw();

	for(int i = 0; i < this->mFlashingLights.size(); i++)
		this->mFlashingLights[i]->draw();

	for(int i = 0; i < this->mTurrets.size(); i++)
		this->mTurrets[i]->draw();

	if(this->isVisible())
	{
		if(this->isSelected())
		{
			ToolsImage::drawBorderCircle(this, ENTITY_BORDER_SELECTED_COLOR, ENTITY_BORDER_SELECTED_SIZE, CIRCLE_SELECTED_SIZE);
			this->mTBDistance.draw();
		}
		else if(this->hasMouseOver())
		{
			ToolsImage::drawBorderCircle(this, ENTITY_BORDER_FOCUS_COLOR, ENTITY_BORDER_FOCUS_SIZE, CIRCLE_SELECTED_SIZE);
		}
	}
}

void Entity::destroy()
{
	AutoManager::add(new ExplosionEffect(this));
}

void Entity::shieldImpact()
{
	if(this->mShieldSprite != NULL)
	{
		this->mShieldSprite->setColor(sf::Color(255, 255, 255, SHIELDIMPACT_ALPHA));
		this->mShieldClock.restart();
	}
}








