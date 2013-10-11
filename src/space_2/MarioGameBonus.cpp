#include "MarioGameBonus.h"
#include "SpriteParameterFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define BONUS_EFFECTTIME		0.25	// sec


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBonus::MarioGameBonus( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlockActive(p_game, p_positionGrid)
{
	this->mBonusState = BonusState::ActiveOne;
	this->notifyBonusStateChanged();
}

MarioGameBonus::~MarioGameBonus(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
MarioGameBonus::BonusState MarioGameBonus::getBonusState()
{
	return this->mBonusState;
}

void MarioGameBonus::setBonusState( BonusState p_state )
{
	if(this->mBonusState != p_state)
	{
		this->mBonusState = p_state;
		this->notifyBonusStateChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBonus::update()
{
	MarioGameBlockActive::update();
	this->updateBonusState();
}

void MarioGameBonus::updateBonusState()
{
	if(this->getBonusState() != BonusState::Inactive && this->mBonusClock.getElapsedTimeAsSeconds() > BONUS_EFFECTTIME)
	{
		if(this->getBonusState() == BonusState::ActiveOne)
			this->setBonusState(BonusState::ActiveTwo);
		else if(this->getBonusState() == BonusState::ActiveTwo)
			this->setBonusState(BonusState::ActiveThree);
		else if(this->getBonusState() == BonusState::ActiveThree)
			this->setBonusState(BonusState::ActiveFour);
		else if(this->getBonusState() == BonusState::ActiveFour)
			this->setBonusState(BonusState::ActiveOne);
		this->mBonusClock.restart();
	}
}

void MarioGameBonus::notifyBonusStateChanged()
{
	if(this->mSprite != NULL)
	{
		delete this->mSprite;
		this->mSprite = NULL;
	}

	switch(this->mBonusState)
	{
	case ActiveOne:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSACTIVEONE);
		break;

	case ActiveTwo:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSACTIVETWO);
		break;

	case ActiveThree:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSACTIVETHREE);
		break;

	case ActiveFour:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSACTIVEFOUR);
		break;

	case Inactive:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSINACTIVE);
		break;
	}
	ToolsImage::setSpriteOriginCenter(this->mSprite);
	this->updatePosition();
}

void MarioGameBonus::BeginContact( b2Contact* p_contact, MarioGameUserData::UserDataIndex p_index )
{
	if(this->getBonusState() != BonusState::Inactive)
	{
		b2WorldManifold worldManifold;
		p_contact->GetWorldManifold(&worldManifold);
		if(worldManifold.points[0].y < this->mBodyBrick->GetPosition().y && this->mGame->getBlock(this->mPositionGrid.x, this->mPositionGrid.y + 1) == NULL)
		{
			MarioGameBlockActive::BeginContact(p_contact, p_index);
			this->setBonusState(BonusState::Inactive);
		}
	}
}
