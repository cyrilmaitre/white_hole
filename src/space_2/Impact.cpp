#include "Impact.h"
#include "Entity.h"
#include "SpriteParameterFactory.h"
#include "ToolsMap.h"
#include "ImageGIFFactory.h"
#include "EntityManager.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Impact::Impact( Entity* p_target, float p_scale )
{
	this->mImpactGif = NULL;
	this->mImpactSprite = NULL;

	this->mTarget.setEntity(p_target);
	this->mScale = 1;
	this->setScale(p_scale);
	this->mLiveTime = 0;
	this->mOffsetX = Tools::random(0, (int)p_target->getHitBox().width) - (p_target->getHitBox().width / 2);
	this->mOffsetY = Tools::random(0, (int)p_target->getHitBox().height) - (p_target->getHitBox().height / 2);
}

Impact::~Impact(void)
{
	if(this->mImpactGif != NULL)
		delete this->mImpactGif;

	if(this->mImpactSprite != NULL)
		delete this->mImpactSprite;
}


//*************************************************************
// Getters - Setters
//*************************************************************
EntityTarget* Impact::getTarget()
{
	return &this->mTarget;
}

float Impact::getScale()
{
	return this->mScale;
}

void Impact::setScale( float p_scale )
{
	if(this->mScale != p_scale)
	{
		this->mScale = p_scale;
		this->notifyScaleChanged();
	}
}

int Impact::getOffsetX()
{
	return this->mOffsetX;
}

void Impact::setOffsetX( int p_x )
{
	this->mOffsetX = p_x;
	this->updatePosition();
}

int Impact::getOffsetY()
{
	return this->mOffsetY;
}

void Impact::setOffsetY( int p_y )
{
	this->mOffsetY = p_y;
	this->updatePosition();
}


//*************************************************************
// Methods
//*************************************************************
void Impact::update()
{
	if(this->mImpactGif != NULL)
		this->mImpactGif->update();
}

void Impact::updatePosition()
{
	if(this->getTarget()->isEntityValid() && this->getTarget()->getEntity()->isVisible())
	{
		if(this->mImpactGif != NULL)
		{
			this->mImpactGif->setPosition(	this->getTarget()->getEntity()->getScreenX() + this->getOffsetX(),
											this->getTarget()->getEntity()->getScreenY() + this->getOffsetY() + this->getTarget()->getEntity()->getRocking());
		}
		
		if(this->mImpactSprite != NULL)
		{
			this->mImpactSprite->setPosition(	this->getTarget()->getEntity()->getScreenX() + this->getOffsetX(), 
												this->getTarget()->getEntity()->getScreenY() + this->getOffsetY() + this->getTarget()->getEntity()->getRocking());
		}
	}
}

void Impact::draw()
{
	if(this->getTarget()->isEntityValid() && this->getTarget()->getEntity()->isVisible())
	{
		this->updatePosition();		
		if(!this->isFinished())
		{
			if(this->mImpactGif != NULL && this->mImpactGif->getLoop() == 0)
				this->mImpactGif->draw();
			
			if(this->mImpactSprite != NULL)
				Resource::resource->getApp()->draw(*this->mImpactSprite);
		}	
	}
}

void Impact::notifyScaleChanged()
{
	if(this->mImpactSprite != NULL)
		this->mImpactSprite->setScale(this->getScale(), this->getScale());
	
	if(this->mImpactGif != NULL)
		this->mImpactGif->getSprite().setScale(this->getScale(), this->getScale());
}



