#include "ImpactExplosion.h"
#include "ImageGIFFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ImpactExplosion::ImpactExplosion( Entity* p_target, float p_scale ) : Impact(p_target)
{
	this->mImpactGif = ImageGIFFactory::getImpactExplosion();
	ToolsImage::setSpriteOriginCenter(&this->mImpactGif->getSprite());
	this->setScale(p_scale);
	this->setLiveTime(this->mImpactGif->getDurationInMilliseconds());
}

ImpactExplosion::~ImpactExplosion(void)
{
}
