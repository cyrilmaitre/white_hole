#include "MarioGameBlockActive.h"
#include "MarioGameCoin.h"
#include "Jukebox.h"


//*************************************************************
// Define
//*************************************************************
#define UPPEDSTATE_TIME				0.08		// sec
#define DOWNEDSTATE_TIME			0.08		// sec
#define UPPEDSTATE_OFFSET			15			// px
#define DOWNEDSTATE_OFFSET			15			// px
#define SOUND_PUMP					"marioGamePump.ogg"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBlockActive::MarioGameBlockActive( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameUserData(MarioGameUserData::UserDataType::BlockActive), MarioGameBlock(p_game, p_positionGrid)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(MarioGame::pixelToMeter(p_positionGrid.x * MARIOGAME_BLOCK_WIDTH + MARIOGAME_BLOCK_WIDTH / 2), MarioGame::pixelToMeter(p_positionGrid.y * MARIOGAME_BLOCK_HEIGHT + MARIOGAME_BLOCK_HEIGHT / 2));
	this->mBodyBrick = this->mGame->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape bodyBox;
	bodyBox.SetAsBox(MarioGame::pixelToMeter(MARIOGAME_BLOCK_WIDTH / 2), MarioGame::pixelToMeter(MARIOGAME_BLOCK_HEIGHT / 2));
	this->mBodyBrick->CreateFixture(&bodyBox, 0.0f);
	this->mBodyBrick->SetUserData(this);

	this->setActiveState(ActiveState::Idle);
}

MarioGameBlockActive::~MarioGameBlockActive(void)
{
	this->mGame->getWorld()->DestroyBody(this->mBodyBrick);
}


//*************************************************************
// Getters - Setters
//*************************************************************
MarioGameBlockActive::ActiveState MarioGameBlockActive::getActiveState()
{
	return this->mActiveState;
}

void MarioGameBlockActive::setActiveState( ActiveState p_state )
{
	this->mActiveState = p_state;
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBlockActive::update()
{
	MarioGameBlock::update();
	b2Vec2 bodyPosition = this->mBodyBrick->GetPosition();
	float activeOffset = 0.0f;
	this->updateActiveState();
	if(this->getActiveState() == ActiveState::Upped)
		activeOffset = (this->mActiveClock.getElapsedTimeAsSeconds() / UPPEDSTATE_TIME) * UPPEDSTATE_OFFSET;
	else if(this->getActiveState() ==  ActiveState::Downed)
		activeOffset = UPPEDSTATE_OFFSET - (this->mActiveClock.getElapsedTimeAsSeconds() / DOWNEDSTATE_TIME) * DOWNEDSTATE_OFFSET;
	this->setPosition(	this->mGame->getX() + MarioGame::meterToPixel(bodyPosition.x), 
						this->mGame->getBottomY() - MarioGame::meterToPixel(bodyPosition.y) - activeOffset);
}

void MarioGameBlockActive::updateActiveState()
{
	if(this->getActiveState() == ActiveState::Idle)
		return;

	if(this->getActiveState() == ActiveState::Upped && this->mActiveClock.getElapsedTimeAsSeconds() >= UPPEDSTATE_TIME)
	{
		this->setActiveState(ActiveState::Downed);
		this->mActiveClock.restart();
	}
	else if(this->getActiveState() == ActiveState::Downed && this->mActiveClock.getElapsedTimeAsSeconds() >= DOWNEDSTATE_TIME)
	{
		this->setActiveState(ActiveState::Idle);
		this->mActiveClock.restart();
	}
}

void MarioGameBlockActive::BeginContact( b2Contact* p_contact, MarioGameUserData::UserDataIndex p_index )
{
	b2WorldManifold worldManifold;
	p_contact->GetWorldManifold(&worldManifold);
	MarioGameBlock* topBlock = this->mGame->getBlock(this->mPositionGrid.x, this->mPositionGrid.y + 1);
	bool topBlockCoin = dynamic_cast<MarioGameCoin*>(topBlock) != NULL;
	if(worldManifold.points[0].y < this->mBodyBrick->GetPosition().y && this->getActiveState() == ActiveState::Idle && (topBlock == NULL || topBlockCoin))
	{
		this->setActiveState(ActiveState::Upped);
		this->mActiveClock.restart();
		Jukebox::getInstance()->playSound(SOUND_PUMP);
	}
}


