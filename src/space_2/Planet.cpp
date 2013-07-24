#include "Planet.h"
#include "ToolsImage.h"

//*************************************************************
// Define
//*************************************************************
#define PLANET_LIGHTCARD_IMG		"planet_lightCard.png"
#define PLANET_LIGHT_IMG_PRE		"planet_lights_"
#define PLANET_LIGHT_IMG_SUF		".png"
#define PLANET_RING_IMG_PRE			"planet_ring_"
#define PLANET_RING_IMG_SUF			".png"
#define PLANET_LIGHT_COUNT			4
#define PLANET_LIGHT_CHANCE			0.5
#define PLANET_RING_COUNT			2
#define PLANET_RING_CHANCE			0.2


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Planet::Planet()
{
	this->mPlanetModel = NULL;
	this->mPlanetLightCard = NULL;
	this->mPlanetLight = NULL;
	this->mPlanetRing = NULL;
	this->mWeight = 0;
	this->mTemp = 0;

	this->mPlanetLightCardRotation = Tools::random(0, 360);
	this->mPlanetLightDraw = Tools::randomZeroToOne() < PLANET_LIGHT_CHANCE;
	if(this->mPlanetLightDraw)
	{
		this->mPlanetLightRotation = Tools::random(0, 360);
		this->mPlanetLightSprite = PLANET_LIGHT_IMG_PRE + Tools::buildStringWithInt(Tools::random(1, PLANET_LIGHT_COUNT)) + PLANET_LIGHT_IMG_SUF;
	}
	this->mPlanetRingDraw = Tools::randomZeroToOne() < PLANET_RING_CHANCE;
	if(this->mPlanetRingDraw)
	{
		this->mPlanetRingRotation = Tools::random(0, 360);
		this->mPlanetRingSprite = PLANET_RING_IMG_PRE + Tools::buildStringWithInt(Tools::random(1, PLANET_RING_COUNT)) + PLANET_RING_IMG_SUF;
	}

	this->setObjectType(MapObjectType::TypePlanet);
	this->desactivateOverable();
}


Planet::~Planet(void)
{
	if(this->mPlanetLightCard != NULL)
		delete this->mPlanetLightCard;

	if(this->mPlanetLight != NULL)
		delete this->mPlanetLight;

	if(this->mPlanetRing != NULL)
		delete this->mPlanetRing;
}


//*************************************************************
// Getters - Setters
//*************************************************************
std::string Planet::getName()
{
	return this->mName;
}

void Planet::setName( std::string p_name )
{
	this->mName = p_name;
}

float Planet::getWeight()
{
	return this->mWeight;
}

void Planet::setWeight( float p_weight )
{
	if(p_weight < 0.f)
		p_weight = 0.f;

	this->mWeight = p_weight;
}

float Planet::getTemp()
{
	return this->mTemp;
}

void Planet::setTemp( float p_temp )
{
	this->mTemp = p_temp;
}

PlanetModel* Planet::getPlanetModel()
{
	return this->mPlanetModel;
}

void Planet::setPlanetModel( PlanetModel* p_model )
{
	this->mPlanetModel = p_model;
	this->notifyPlanetModelChanged();
}


//*************************************************************
// Method
//*************************************************************
void Planet::updateSprite()
{
	MapObject::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mPlanetLightCard != NULL)
		this->mPlanetLightCard->setPosition(objectPositionScreen.x, objectPositionScreen.y);

	if(this->mPlanetLight != NULL)
		this->mPlanetLight->setPosition(objectPositionScreen.x, objectPositionScreen.y);

	if(this->mPlanetRing != NULL)
		this->mPlanetRing->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void Planet::draw()
{
	MapObject::draw();

	if(this->mPlanetRing != NULL)
		Resource::resource->getApp()->draw(*this->mPlanetRing);

	if(this->mPlanetLightCard != NULL)
		Resource::resource->getApp()->draw(*this->mPlanetLightCard);

	if(this->mPlanetLight != NULL)
		Resource::resource->getApp()->draw(*this->mPlanetLight);
}

void Planet::loadSprite()
{
	MapObject::loadSprite();

	if(this->getPlanetModel() != NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(this->getPlanetModel()->getSprite()));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
		this->mObjectSprite->setRotation(this->getRotation());
		this->mObjectSprite->setScale(this->mScale, this->mScale);

		this->mPlanetLightCard = new sf::Sprite(*Resource::resource->getTexture(PLANET_LIGHTCARD_IMG));
		ToolsImage::setSpriteOriginCenter(this->mPlanetLightCard);
		this->mPlanetLightCard->setRotation(this->mPlanetLightCardRotation);
		this->mPlanetLightCard->setScale(this->mScale, this->mScale);

		if(this->mPlanetLightDraw)
		{
			this->mPlanetLight = new sf::Sprite(*Resource::resource->getTexture(this->mPlanetLightSprite));
			ToolsImage::setSpriteOriginCenter(this->mPlanetLight);
			this->mPlanetLight->setRotation(this->mPlanetLightRotation);
			this->mPlanetLight->setScale(this->mScale, this->mScale);
		}

		if(this->mPlanetRingDraw)
		{
			this->mPlanetRing = new sf::Sprite(*Resource::resource->getTexture(this->mPlanetRingSprite));
			ToolsImage::setSpriteOriginCenter(this->mPlanetRing);
			this->mPlanetRing->setRotation(this->mPlanetRingRotation);
			this->mPlanetRing->setScale(this->mScale, this->mScale);
		}

		this->updateSprite();
	}
}

void Planet::unloadSprite()
{
	MapObject::unloadSprite();

	if(this->mPlanetLightCard != NULL)
	{
		delete this->mPlanetLightCard;
		this->mPlanetLightCard = NULL;
	}

	if(this->mPlanetLight != NULL)
	{
		delete this->mPlanetLight;
		this->mPlanetLight = NULL;
	}

	if(this->mPlanetRing != NULL)
	{
		delete this->mPlanetRing;
		this->mPlanetRing = NULL;
	}
}

void Planet::notifyPlanetModelChanged()
{
	if(this->getPlanetModel() != NULL)
	{
		this->setPlane(this->getPlanetModel()->getRandomPlane());
		this->setWeight(this->getPlanetModel()->getRandomWeight());
		this->setTemp(this->getPlanetModel()->getRandomWeight());
		this->setScale(this->getPlanetModel()->getRandomScale());
		this->setSize(this->getPlanetModel()->getHitBoxWidth(), this->getPlanetModel()->getHitBoxHeight());
		this->loadSprite();
	}
}

