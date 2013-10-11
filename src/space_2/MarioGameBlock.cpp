#include "MarioGameBlock.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBlock::MarioGameBlock(MarioGame* p_game, sf::Vector2i p_positionGrid)
{
	this->mSprite = NULL;
	this->mGame = p_game;
	this->mPositionGrid = p_positionGrid;
}

MarioGameBlock::~MarioGameBlock(void)
{
	if(this->mSprite != NULL)
		delete this->mSprite;
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBlock::update()
{
}

void MarioGameBlock::updatePosition()
{
	this->mSprite->setPosition(this->getX(), this->getY());
}

void MarioGameBlock::draw()
{
	if(this->mSprite != NULL)
		Resource::resource->getApp()->draw(*this->mSprite);
}

void MarioGameBlock::notifyPositionChanged()
{
	Object::notifyPositionChanged();
	this->updatePosition();
}
