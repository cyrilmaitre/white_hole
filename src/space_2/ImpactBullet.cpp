#include "ImpactBullet.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define LIVETIME	100 // ms


//*************************************************************
// Constructor - Destructor
//*************************************************************
ImpactBullet::ImpactBullet( Entity* p_target, float p_scale ) : Impact(p_target)
{
	this->mImpactSprite = new sf::Sprite(*Resource::resource->getTexture(IMG_IMPACT_BULLET));
	ToolsImage::setSpriteOriginCenter(this->mImpactSprite);
	this->setScale(p_scale);
	this->setLiveTime(LIVETIME);
}

ImpactBullet::~ImpactBullet(void)
{
}
