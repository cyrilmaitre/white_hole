#include "Entity.h"
#include "SpriteParameterFactory.h"
#include "Camera.h"
#include "ToolsImage.h"
#include "Game.h"
#include "AutoManager.h"
#include "ExplosionEffect.h"
#include "FlashingLightEffect.h"
#include "NpcType.h"
#include "WreckManager.h"


//*************************************************************
// Define
//*************************************************************
#define CIRCLE_SELECTED_SIZE			100
#define SHIELDIMPACT_ALPHA				100
#define SHIELDIMPACT_ALPHARECOVER		50		// per sec
#define TARGET_HITBOX_OFFSET			0.6		// per one


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Entity::Entity( int p_plane ) : MapObject(p_plane)
{
	this->mTargetOffsetX = 0;
	this->mTargetOffsetY = 0;

	this->mShieldSprite = NULL;
	this->mWeaponEffectCurrent = 0;
	this->mTBDistance.setFontColor(ENTITY_DISTANCE_FONT_COLOR);
	this->mTBDistance.setFontSize(ENTITY_DISTANCE_FONT_SIZE);
	this->mTBDistance.setText(Tools::buildStringWithInt(0) + Resource::resource->getBundle()->getString("meterAb"));
}

Entity::~Entity(void)
{
	if(this->mShieldSprite != NULL)
		delete this->mShieldSprite;

	for(int i = 0; i < this->mRadarEffects.size(); i++)
		delete this->mRadarEffects[i];
	this->mRadarEffects.clear();

	for(int i = 0; i < this->mFlashingLightEffects.size(); i++)
		delete this->mFlashingLightEffects[i];
	this->mFlashingLightEffects.clear();

	for(int i = 0; i < this->mWeaponEffects.size(); i++)
		delete this->mWeaponEffects[i];
	this->mWeaponEffects.clear();

	for(int i = 0; i < this->mTurretEffects.size(); i++)
		delete this->mTurretEffects[i];
	this->mTurretEffects.clear();
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityTarget* Entity::getTarget()
{
	return &this->mTarget;
}

double Entity::getTargetOffsetX()
{
	return this->mTargetOffsetX;
}

void Entity::setTargetOffsetX( double p_x )
{
	this->mTargetOffsetX = p_x;
}

double Entity::getTargetOffsetY()
{
	return this->mTargetOffsetY;
}

void Entity::setTargetOffsetY( double p_y )
{
	this->mTargetOffsetY = p_y;
}

bool Entity::isDestroy()
{
	return !this->hasStructure();
}

WeaponEffect* Entity::getWeaponToFire()
{
	if(this->mWeaponEffects.size() > 0)
	{
		WeaponEffect* returnValue = this->mWeaponEffects[this->mWeaponEffectCurrent];
		this->selectNextWeapon();
		return returnValue;
	}
	return NULL;
}


//*************************************************************
// Methods
//*************************************************************
void Entity::update()
{
	if(this->getTarget() != NULL && this->getTarget()->isEntityChanged())
		this->notifyTargetChanged();

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

	for(int i = 0; i < this->mRadarEffects.size(); i++)
		this->mRadarEffects[i]->update();

	for(int i = 0; i < this->mTurretEffects.size(); i++)
		this->mTurretEffects[i]->update();

	for(int i = 0; i < this->mWeaponEffects.size(); i++)
		this->mWeaponEffects[i]->update();

	for(int i = 0; i < this->mFlashingLightEffects.size(); i++)
		this->mFlashingLightEffects[i]->update();
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
	MapObject::notifyRotationChanged();

	if(this->mShieldSprite != NULL)
		this->mShieldSprite->setRotation(this->getRotation());
}

void Entity::notifyFlashingLightJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mFlashingLightEffects.size(); i++)
		delete this->mFlashingLightEffects[i];
	this->mFlashingLightEffects.clear();

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
				this->mFlashingLightEffects.push_back(new FlashingLightEffect(this, currentJson));
		}
	}
}

void Entity::notifyRadarJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mRadarEffects.size(); i++)
		delete this->mRadarEffects[i];
	this->mRadarEffects.clear();

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
				this->mRadarEffects.push_back(new RadarEffect(this, currentJson));
		}
	}
}

void Entity::notifyTurretJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mTurretEffects.size(); i++)
		delete this->mTurretEffects[i];
	this->mTurretEffects.clear();

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
				this->mTurretEffects.push_back(new TurretEffect(this, currentJson));
		}
	}
}

void Entity::notifyWeaponJsonChanged()
{
	// Delete
	for(int i = 0; i < this->mWeaponEffects.size(); i++)
		delete this->mWeaponEffects[i];
	this->mWeaponEffects.clear();

	// Add
	Json::Value jsonWeapon;   
	Json::Reader reader;
	bool parsingSuccessfull = reader.parse(this->getWeaponJson(), jsonWeapon);
	if(parsingSuccessfull && jsonWeapon.isArray())
	{
		for(int i = 0; i < jsonWeapon.size(); i++)
		{
			Json::Value currentJson = jsonWeapon.get(i, NULL);
			if(currentJson != NULL)
				this->mWeaponEffects.push_back(new WeaponEffect(this, currentJson));
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

	if(this->isVisible())
	{
		for(int i = 0; i < this->mRadarEffects.size(); i++)
			this->mRadarEffects[i]->draw();

		for(int i = 0; i < this->mTurretEffects.size(); i++)
			this->mTurretEffects[i]->draw();

		for(int i = 0; i < this->mWeaponEffects.size(); i++)
			this->mWeaponEffects[i]->draw();

		for(int i = 0; i < this->mFlashingLightEffects.size(); i++)
			this->mFlashingLightEffects[i]->draw();

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
	if(this->getObjectType() != MapObjectType::TypeWreck && this->getObjectType() != MapObjectType::TypeWreckMini)
		AutoManager::add(new ExplosionEffect(this));
	else
		AutoManager::add(new ExplosionEffect(this, false));

	if(this->getObjectType() != MapObjectType::TypeWreck && this->getObjectType() != MapObjectType::TypeWreckMini)
		WreckManager::add(new Wreck(this));
}

void Entity::shieldImpact()
{
	if(this->mShieldSprite != NULL)
	{
		this->mShieldSprite->setColor(sf::Color(255, 255, 255, SHIELDIMPACT_ALPHA));
		this->mShieldClock.restart();
	}
}

void Entity::selectNextWeapon()
{
	this->mWeaponEffectCurrent++;
	if(this->mWeaponEffectCurrent >= this->mWeaponEffects.size())
		this->mWeaponEffectCurrent = 0;
}

void Entity::addWeaponEffect( WeaponEffect* p_weapon )
{
	this->mWeaponEffects.push_back(p_weapon);
}

void Entity::notifyNpcTypeChanged( NpcType* p_type )
{
	if(p_type != NULL)
	{
		for(int i = 0; i < this->mFlashingLightEffects.size(); i++)
		{
			this->mFlashingLightEffects[i]->setLightColor(p_type->getLightColor());
		}
	}
}

void Entity::notifyTargetChanged()
{
	if(this->getTarget() != NULL && this->getTarget()->isEntityValid())
	{
		int hitBoxWidth = (int)((float)this->getTarget()->getEntity()->getHitBox().width * TARGET_HITBOX_OFFSET);
		int hitBoxHeight = (int)((float)this->getTarget()->getEntity()->getHitBox().height * TARGET_HITBOX_OFFSET);
		this->setTargetOffsetX(Tools::random(0, hitBoxWidth) - (hitBoxWidth / 2));
		this->setTargetOffsetY(Tools::random(0, hitBoxHeight) - (hitBoxHeight / 2));
	}
}

