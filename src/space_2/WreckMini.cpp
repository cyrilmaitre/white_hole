#include "WreckMini.h"
#include "ToolsImage.h"
#include "Wreck.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define SPRITE_BASE_PRE				"debris_"
#define SPRITE_BASE_SUF				".png"
#define SPRITE_EMBER_PRE			"debris_ember_"
#define SPRITE_EMBER_SUF			".png"
#define SPRITE_COUNT				6
#define QUICKENING					100
#define VELOCITY_MIN				250
#define VELOCITY_MAX				500
#define SIZE						32
#define ROTATION_VELOCITY_MIN		5
#define ROTATION_VELOCITY_MAX		50


//*************************************************************
// Constructor - Destructor
//*************************************************************
WreckMini::WreckMini( Wreck* p_parent )
{
	this->setRockingActived(false);
	this->setVelocityMax(Tools::random(VELOCITY_MIN, VELOCITY_MAX));
	for(int i = 0; i < 8; i++)
		this->setVelocityAt((MovableCardinality)i, Tools::random(0, this->getVelocityMax()));
	this->setQuickening(QUICKENING);
	this->setSize(SIZE, SIZE);
	this->setPosition(p_parent->Object::getX(), p_parent->Object::getY());
	this->setRotationInfinite(true);
	this->setRotationInfiniteRight(Tools::randomBool());
	this->setRotationVelocity(Tools::random(ROTATION_VELOCITY_MIN, ROTATION_VELOCITY_MAX));
	
	this->mSpriteId = Tools::random(1, SPRITE_COUNT);
}

WreckMini::~WreckMini(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WreckMini::update()
{
	EntityMovable::update();
}

void WreckMini::updateSprite()
{
	EntityMovable::updateSprite();
}

void WreckMini::loadSprite()
{
	EntityMovable::loadSprite();

	if(this->mObjectSprite == NULL)
	{
		this->mObjectSprite = new sf::Sprite(*Resource::resource->getTexture(SPRITE_BASE_PRE + Tools::buildStringWithInt(this->mSpriteId) + SPRITE_BASE_SUF));
		ToolsImage::setSpriteOriginCenter(this->mObjectSprite);
	}
}

void WreckMini::draw()
{
	EntityMovable::draw();
}
