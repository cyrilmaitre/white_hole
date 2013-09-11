#include "ImpactLaser.h"
#include "ImageGIFFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ImpactLaser::ImpactLaser( Entity* p_target, int p_offsetX, int p_offsetY, float p_scale ) : Impact(p_target, p_offsetX, p_offsetY)
{
	this->mImpactGif = ImageGIFFactory::getImpactLaser();
	ToolsImage::setSpriteOriginCenter(&this->mImpactGif->getSprite());
	this->setScale(p_scale);
	this->setLiveTime(this->mImpactGif->getDurationInMilliseconds());
}

ImpactLaser::~ImpactLaser(void)
{
}
