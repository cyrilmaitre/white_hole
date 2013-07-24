#include "ExplosionEffect.h"
#include "ImageGIFFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ExplosionEffect::ExplosionEffect(Entity* p_entity)
{
	this->mExplosionGif = NULL;
	this->mLiveTime = 0;

	this->setX(p_entity->Object::getX());
	this->setY(p_entity->Object::getY());
	this->setWidth(p_entity->Object::getWidth());
	this->setHeight(p_entity->Object::getHeight());

	this->configureExplosion(p_entity);
}

ExplosionEffect::~ExplosionEffect(void)
{
	if(this->mExplosionGif != NULL)
		delete this->mExplosionGif;
}


//*************************************************************
// Methods
//*************************************************************
void ExplosionEffect::update()
{
	EffectMap::update();

	if(this->mExplosionGif != NULL)
		this->mExplosionGif->update();

	this->updatePosition();
}

void ExplosionEffect::updatePosition()
{
	if(this->isVisible())
	{
		if(this->mExplosionGif != NULL)
		{
			this->mExplosionGif->setX(this->getScreenX());
			this->mExplosionGif->setY(this->getScreenY());
		}
	}
}

void ExplosionEffect::draw()
{
	if(this->isVisible())
	{
		if(!this->isFinished())
		{
			if(this->mExplosionGif != NULL && this->mExplosionGif->getLoop() == 0)
				this->mExplosionGif->draw();
		}	
	}
}

void ExplosionEffect::configureExplosion( Entity* p_entity )
{
	switch(p_entity->getExplosionSize())
	{
	case DESTRCUTABLE_EXPLOSIONSIZE_SMALL:
		this->mExplosionGif = ImageGIFFactory::getExplosionSmall();
		break;

	case DESTRCUTABLE_EXPLOSIONSIZE_MEDIUM:
		this->mExplosionGif = ImageGIFFactory::getExplosionMedium();
		break;  

	case DESTRCUTABLE_EXPLOSIONSIZE_LARGE:
		this->mExplosionGif = ImageGIFFactory::getExplosionLarge();
		break;
	}

	if(this->mExplosionGif != NULL)
	{
		this->mExplosionGif->getSprite().setOrigin(this->mExplosionGif->getSprite().getLocalBounds().width / 2, this->mExplosionGif->getSprite().getLocalBounds().height / 2);
		this->setLiveTime(this->mExplosionGif->getDurationInMilliseconds());
		this->updatePosition();
	}
}
