#include "ReactorDustEffect.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define REACTORDUST_SPRITE		"reactor_wisp.png"
#define REACTORDUST_LIVETIME	1000.f	// millisec


//*************************************************************
// Constructor - Destructor
//*************************************************************
ReactorDustEffect::ReactorDustEffect( double p_x, double p_y, float p_size, float p_alpha )
{
	this->setPosition(p_x, p_y);
	this->mSize = p_size;
	this->mAlpha = p_alpha;
	this->setVisible(true);
	this->setLiveTime(REACTORDUST_LIVETIME);
}

ReactorDustEffect::~ReactorDustEffect(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ReactorDustEffect::update()
{
	EffectMap::update();
	this->updateSpriteSize();
}

void ReactorDustEffect::updateSpriteSize()
{
	float newSize = this->mSize * (1.f - ((float)this->mClockReactorDust.getElapsedTimeAsMilliseconds() / REACTORDUST_LIVETIME));
	ToolsImage::resizeSprite(this->mObjectSprite, newSize, newSize);
}

void ReactorDustEffect::loadSprite()
{
	MapObject::loadSprite();

	this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(REACTORDUST_SPRITE));
	ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	ToolsImage::resizeSprite(this->mObjectSprite, this->mSize, this->mSize);
	this->mObjectSprite->setColor(sf::Color(255, 255, 255, this->mAlpha));
	this->updateSprite();
}


