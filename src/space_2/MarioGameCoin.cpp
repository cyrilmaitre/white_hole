#include "MarioGameCoin.h"
#include "ToolsImage.h"
#include "SpriteParameterFactory.h"
#include "Jukebox.h"


//*************************************************************
// Define
//*************************************************************
#define COIN_EFFECTFRAME_TIME		0.40f	// sec
#define COIN_VALUE					10.0	// credit
#define COIN_SOUND					"marioGameCoin.ogg"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameCoin::MarioGameCoin( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlock(p_game, p_positionGrid), MarioGameUserData(UserDataType::Coin)
{ 
	b2BodyDef bodyDef;
	bodyDef.position.Set(MarioGame::pixelToMeter(p_positionGrid.x * MARIOGAME_BLOCK_WIDTH + MARIOGAME_BLOCK_WIDTH / 2), MarioGame::pixelToMeter(p_positionGrid.y * MARIOGAME_BLOCK_HEIGHT + MARIOGAME_BLOCK_HEIGHT / 2));
	this->mBodyCoin = this->mGame->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape bodyBox;
	bodyBox.SetAsBox(MarioGame::pixelToMeter(MARIOGAME_COIN_WIDTH / 2), MarioGame::pixelToMeter(MARIOGAME_COIN_HEIGHT / 2));
	this->mBodyCoin->CreateFixture(&bodyBox, 0.0f);
	this->mBodyCoin->SetUserData(this);

	this->mCoinState = CoinState::ActiveOne;
	this->notifyCoinStateChanged();
}

MarioGameCoin::~MarioGameCoin(void)
{
	this->mGame->getWorld()->DestroyBody(this->mBodyCoin);
}


//*************************************************************
// Getters - Setters
//*************************************************************
MarioGameCoin::CoinState MarioGameCoin::getCoinState()
{
	return this->mCoinState;
}

void MarioGameCoin::setCoinState( CoinState p_state )
{
	if(this->mCoinState != p_state)
	{
		this->mCoinState = p_state;
		this->notifyCoinStateChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameCoin::update()
{
	MarioGameBlock::update();
	this->updateCoinState();
	b2Vec2 bodyPosition = this->mBodyCoin->GetPosition();
	this->setPosition(	this->mGame->getX() + MarioGame::meterToPixel(bodyPosition.x), 
						this->mGame->getBottomY() - MarioGame::meterToPixel(bodyPosition.y));
}

void MarioGameCoin::updateCoinState()
{
	if(this->mCoinClock.getElapsedTimeAsSeconds() > COIN_EFFECTFRAME_TIME)
	{
		if(this->getCoinState() == CoinState::ActiveOne)
			this->setCoinState(CoinState::ActiveTwo);
		else if(this->getCoinState() == CoinState::ActiveTwo)
			this->setCoinState(CoinState::ActiveThree);
		else if(this->getCoinState() == CoinState::ActiveThree)
			this->setCoinState(CoinState::ActiveOne);
		this->mCoinClock.restart();
	}
}

void MarioGameCoin::notifyCoinStateChanged()
{
	if(this->mSprite != NULL)
	{
		delete this->mSprite;
		this->mSprite = NULL;
	}

	switch(this->mCoinState)
	{
	case CoinState::ActiveOne:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_COINONE);
		break;

	case CoinState::ActiveTwo:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_COINTWO);
		break;

	case CoinState::ActiveThree:
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_COINTHREE);
		break;

	case CoinState::Destroy:
		Jukebox::getInstance()->playSound(COIN_SOUND);
		break;
	}

	if(this->mSprite != NULL)
	{
		ToolsImage::setSpriteOriginCenter(this->mSprite);
		this->updatePosition();
	}
}

void MarioGameCoin::PreSolve( b2Contact* p_contact, const b2Manifold* p_oldManifold, UserDataIndex p_index )
{
	this->setCoinState(CoinState::Destroy);
	p_contact->SetEnabled(false);
	this->mGame->incCredit(COIN_VALUE * MARIOGAME_VALUE_MULTIPLIER);
}

