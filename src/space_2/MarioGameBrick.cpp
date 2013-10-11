#include "MarioGameBrick.h"
#include "SpriteParameterFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define BRICK_EFFECTTICK_MIN		8.0f	// sec
#define BRICK_EFFECTTICK_MAX		20.0f	// sec
#define BRICK_EFFECTFRAME_TIME		0.1f	// sec


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBrick::MarioGameBrick( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlockActive(p_game, p_positionGrid)
{
	this->setUserDataType(UserDataType::Brick);
	this->updateNextEffectTick();
	this->mBrickState = BrickState::Idle;
	this->notifyBrickStateChanged();
}

MarioGameBrick::~MarioGameBrick(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
MarioGameBrick::BrickState MarioGameBrick::getBrickState()
{
	return this->mBrickState;
}

void MarioGameBrick::setBrickState( BrickState p_state )
{
	if(this->mBrickState != p_state)
	{
		this->mBrickState = p_state;
		this->notifyBrickStateChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBrick::update()
{
	MarioGameBlockActive::update();	
	this->updateBrickState();
}

void MarioGameBrick::updateBrickState()
{
	if(this->getBrickState() == BrickState::Idle && this->mBrickClock.getElapsedTimeAsSeconds() > this->mNextEffectTick)
	{
		this->updateNextEffectTick();
		this->setBrickState(BrickState::EffectOne);
		this->mBrickClock.restart();
	}
	else if(this->getBrickState() != BrickState::Idle)
	{
		if(this->mBrickClock.getElapsedTimeAsSeconds() > BRICK_EFFECTFRAME_TIME)
		{
			if(this->getBrickState() == BrickState::EffectOne)
				this->setBrickState(BrickState::EffectTwo);
			else if(this->getBrickState() == BrickState::EffectTwo)
				this->setBrickState(BrickState::EffectThree);
			else if(this->getBrickState() == BrickState::EffectThree)
				this->setBrickState(BrickState::EffectFour);
			else if(this->getBrickState() == BrickState::EffectFour)
				this->setBrickState(BrickState::Idle);
			this->mBrickClock.restart();
		}
	}
}

void MarioGameBrick::updateNextEffectTick()
{
	this->mNextEffectTick = Tools::random(BRICK_EFFECTTICK_MIN, BRICK_EFFECTTICK_MAX);
}

void MarioGameBrick::notifyBrickStateChanged()
{
	if(this->mSprite != NULL)
	{
		delete this->mSprite;
		this->mSprite = NULL;
	}

	switch(this->mBrickState)
	{
	case Idle:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICKONE);
		break;

	case EffectOne:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICKTWO);
		break;

	case EffectTwo:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICKTHREE);
		break;

	case EffectThree:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICKFOUR);
		break;

	case EffectFour:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICKFIVE);
		break;
	}
	ToolsImage::setSpriteOriginCenter(this->mSprite);
	this->updatePosition();
}



