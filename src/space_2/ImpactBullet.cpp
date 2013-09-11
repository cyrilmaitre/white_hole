#include "ImpactBullet.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define LIVETIME	100 // ms


//*************************************************************
// Constructor - Destructor
//*************************************************************
ImpactBullet::ImpactBullet( Entity* p_target, int p_offsetX, int p_offsetY, float p_scale ) : Impact(p_target, p_offsetX, p_offsetY)
{
	this->mImpactSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_IMPACT_BULLET));
	ToolsImage::setSpriteOriginCenter(this->mImpactSprite);
	this->setScale(p_scale);
	this->setLiveTime(LIVETIME);
}

ImpactBullet::~ImpactBullet(void)
{
}
