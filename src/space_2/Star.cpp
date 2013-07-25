#include "Star.h"
#include "Sector.h"
#include "ToolsImage.h"
#include "Camera.h"
#include "Game.h"
#include "ToolsMap.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
#define DAZZLE_SPEED					4.f // degree per sec
#define DAZZLE_SIZE_MUL					4.f
#define DAZZLE_ALPHA					100
#define DAZZLE_SPRITE					"star_dazzle.png"		
#define COVERAGE_FOR_DAZZLE_0			1.f
#define DAZZLE_PERCENTMIN				0.01
#define STAR_COLOR						sf::Color(240, 240, 240)


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
Star::Star(void)
{
	this->setObjectType(MapObjectType::TypeStar);
	this->setPlane(STAR_PLANE);
	this->desactivateOverable();

	this->mStarModel = NULL;
	this->mDazzle = NULL;
	this->mDazzleRotation = 0;
	this->mDazzlePercent = 1;
}

Star::~Star(void)
{
	if(this->mDazzle != NULL)
		delete this->mDazzle;
}


//*************************************************************
// Getters - Setters
//*************************************************************
StarModel* Star::getStarModel()
{
	return this->mStarModel;
}

void Star::setStarModel( StarModel* p_model )
{
	if(this->mStarModel != p_model)
	{
		this->mStarModel = p_model;
		this->notifyStarModelChanged();
	}
}

float Star::getDazzleRotation()
{
	return this->mDazzleRotation;
}

void Star::setDazzleRotation( float p_rotation )
{
	if(this->mDazzleRotation != p_rotation)
	{
		if(this->mDazzleRotation >= 360)
			this->mDazzleRotation = 0;

		this->mDazzleRotation = p_rotation;
		this->notifyDazzleRotationChanged();
	}
}

float Star::getDazzlePercent()
{
	return this->mDazzlePercent;
}

void Star::setDazzlePercent( float p_percent )
{
	if(this->mDazzlePercent != p_percent)
	{
		this->mDazzlePercent = p_percent;
		this->notifyDazzlePercentChanged();
	}
}

sf::Color Star::getDazzleColor()
{
	return this->mDazzleColor;
}

void Star::setDazzleColor( sf::Color p_color )
{
	p_color.a = DAZZLE_ALPHA;
	if(this->mDazzleColor != p_color)
	{
		this->mDazzleColor = p_color;

	}
}


//*************************************************************
// Methods
//*************************************************************
void Star::update()
{
	MapObject::update();

	// Update dazzle rotation
	this->setDazzleRotation(this->getDazzleRotation() + DAZZLE_SPEED * this->mClockDazzle.getElapsedTimeAsSeconds());
	this->mClockDazzle.restart();	
}

void Star::updateDazzle()
{
	float newDazzlePercent = 1.f;
	if(this->getSector() != NULL)
	{
		std::vector<Sector*> listSector;
		Game::game->getMap()->getAdjacentSectors(this->getSector(), listSector);
		listSector.push_back(this->getSector());

		for(int i = 0; i < listSector.size(); i++)
		{
			for(int j = 0; j < listSector[i]->getObjectsCount(); j++)
			{
				MapObject* currentObject = listSector[i]->getObject(j);
				if(!ToolsMap::isStar(currentObject))
				{
					float tmpDazzlePercent = this->computeDazzlePercent(currentObject);
					if(tmpDazzlePercent < newDazzlePercent)
						newDazzlePercent = tmpDazzlePercent;
				}
			}

			for(int j = 0; j < listSector[i]->getEntitiesCount(); j++)
			{
				MapObject* currentObject = listSector[i]->getEntity(j);
				float tmpDazzlePercent = this->computeDazzlePercent(currentObject);
				if(tmpDazzlePercent < newDazzlePercent)
					newDazzlePercent = tmpDazzlePercent;
			}
		}
	}
	this->setDazzlePercent(newDazzlePercent);
}

float Star::computeDazzlePercent( MapObject* p_object )
{
	if(p_object->getObjectOpacity() < MapObjectOpacity::Opacity0)
	{
		float coverage = p_object->coverPercent(this);
		if(coverage > 0.f)
		{
			if(coverage > COVERAGE_FOR_DAZZLE_0)
				coverage = COVERAGE_FOR_DAZZLE_0;
			float tmpDazzlePercent =  1.f - coverage / COVERAGE_FOR_DAZZLE_0;
			float opacityPercent = (float)p_object->getObjectOpacity() / 100.f;
			if(tmpDazzlePercent < opacityPercent)
				tmpDazzlePercent = opacityPercent;
			return tmpDazzlePercent;
		}
	}
	return 1.f;
}

void Star::loadSprite()
{
	MapObject::loadSprite();

	if(this->getStarModel() != NULL)
	{
		this->mObjectSprite = new sf::Sprite;
		this->mObjectSprite->setTexture(*Resource::resource->getTexture(this->getStarModel()->getSprite()));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
		this->mObjectSprite->setRotation(this->getRotation());
		this->mObjectSprite->setScale(this->mScale, this->mScale);
		this->mObjectSprite->setColor(STAR_COLOR);
	}

	this->mDazzle = new sf::Sprite;
	this->mDazzle->setTexture(*Resource::resource->getTexture(DAZZLE_SPRITE));
	ToolsImage::setSpriteOriginCenter(this->mDazzle);
	ToolsImage::resizeSprite(this->mDazzle, this->mHitBox.width * DAZZLE_SIZE_MUL * this->getDazzlePercent(), this->mHitBox.height * DAZZLE_SIZE_MUL * this->getDazzlePercent());
	this->mDazzle->setColor(this->mDazzleColor);
	this->mDazzle->setRotation(this->mDazzleRotation);

	this->updateSprite();
}

void Star::unloadSprite()
{
	MapObject::unloadSprite();

	if(this->mDazzle != NULL)
	{
		delete this->mDazzle;
		this->mDazzle = NULL;
	}
}

void Star::updateSprite()
{
	MapObject::updateSprite();

	sf::Vector2f objectPositionScreen = this->getScreenPosition();
	if(this->mDazzle != NULL)
		this->mDazzle->setPosition(objectPositionScreen.x, objectPositionScreen.y);
}

void Star::drawDazzle()
{
	if(this->isVisible())
	{
		if(this->mDazzle != NULL && this->getDazzlePercent() > DAZZLE_PERCENTMIN)
			Resource::resource->getApp()->draw(*this->mDazzle);
	}
}

void Star::notifyDazzlePercentChanged()
{
	if(this->getDazzlePercent() > DAZZLE_PERCENTMIN)
		ToolsImage::resizeSprite(this->mDazzle, this->mHitBox.width * DAZZLE_SIZE_MUL * this->getDazzlePercent(), this->mHitBox.height * DAZZLE_SIZE_MUL * this->getDazzlePercent());	
}

void Star::notifyDazzleRotationChanged()
{
	this->mDazzle->setRotation(this->mDazzleRotation);
}

void Star::notifyDazzleColorChanged()
{
	this->mDazzle->setColor(this->mDazzleColor);
}

void Star::notifyStarModelChanged()
{
	if(this->getStarModel() != NULL)
	{
		this->setScale(this->getStarModel()->getRandomScale());
		this->setSize(this->getStarModel()->getHitBoxWidth(), this->getStarModel()->getHitBoxHeight());
		this->loadSprite();
	}
}





