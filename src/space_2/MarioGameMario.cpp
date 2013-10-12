#include "MarioGameMario.h"
#include "SpriteParameterFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define MARIO_INITAL_POSITIONX		1
#define MARIO_INITAL_POSITIONY		2
#define MARIO_RUNNING_TICK			0.1	// sec
#define MARIO_DIRECTION_RIGHT		true
#define MARIO_DIRECTION_LEFT		false


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameMario::MarioGameMario( MarioGame* p_game ) : MarioGameUserData(MarioGameUserData::UserDataType::Mario)
{
	this->mSprite = NULL;
	this->mGame = p_game;
	this->mWorld = p_game->getWorld();
	
	// Define body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(MARIO_INITAL_POSITIONX, MARIO_INITAL_POSITIONY);
	this->mBody = this->mWorld->CreateBody(&bodyDef);

	// Define shape
	b2PolygonShape shapeBox;
	shapeBox.SetAsBox(MarioGame::pixelToMeter(MARIOGAME_MARIO_WIDTH / 2), MarioGame::pixelToMeter(MARIOGAME_MARIO_HEIGHT / 2));

	// Define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shapeBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	this->mBody->CreateFixture(&fixtureDef);
	this->mBody->SetUserData(this);

	// Define state
	this->mMarioDirection = MARIO_DIRECTION_RIGHT;
	this->mMarioState == MarioState::Idle;
	this->notifyMarioStateChanged();
}

MarioGameMario::~MarioGameMario(void)
{
	if(this->mSprite != NULL)
		delete this->mSprite;

	if(this->mWorld != NULL && this->mBody != NULL)
		this->mWorld->DestroyBody(this->mBody);
}


//*************************************************************
// Getters - Setters
//*************************************************************
MarioGameMario::MarioState MarioGameMario::getMarioState()
{
	return this->mMarioState;
}

void MarioGameMario::setMarioState( MarioState p_state )
{
	if(this->mMarioState != p_state)
	{
		this->mMarioState = p_state;
		this->notifyMarioStateChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameMario::resetPosition()
{
	this->mBody->SetTransform(b2Vec2(MARIO_INITAL_POSITIONX, MARIO_INITAL_POSITIONY), this->mBody->GetAngle());
}

void MarioGameMario::update()
{
	// Update velocity
	b2Vec2 currentVelocity = this->mBody->GetLinearVelocity();
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->mBody->SetLinearVelocity(b2Vec2(12.0f, currentVelocity.y));
		this->mMarioDirection = MARIO_DIRECTION_RIGHT;
	}
	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->mBody->SetLinearVelocity(b2Vec2(-12.0f, currentVelocity.y));
		this->mMarioDirection = MARIO_DIRECTION_LEFT;
	}
	else 
	{
		this->mBody->SetLinearVelocity(b2Vec2(0.0f, currentVelocity.y));
	}

	if( this->getMarioState() != MarioState::Jumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->mBody->ApplyLinearImpulse(b2Vec2(0.0f, 25.0f), this->mBody->GetPosition());
		this->setMarioState(MarioState::Jumping);
	}

	// Update state
	this->updateMarioState();

	// Update sprite position
	b2Vec2 bodyPosition = this->mBody->GetPosition();
	this->mSprite->setPosition(	this->mGame->getX() + MarioGame::meterToPixel(bodyPosition.x), 
								this->mGame->getBottomY() - MarioGame::meterToPixel(bodyPosition.y));
}

void MarioGameMario::updateMarioState()
{
	b2Vec2 currentVelocity = this->mBody->GetLinearVelocity();
	if(this->getMarioState() != MarioState::Jumping)
	{
		if(currentVelocity.x < 0 || currentVelocity.x > 0)
		{
			if(this->getMarioState() != MarioState::RunningOne && this->getMarioState() != MarioState::RunningTwo)
			{
				if(this->getMarioState() != MarioState::RunningThree || this->mClockRunning.getElapsedTimeAsSeconds() > MARIO_RUNNING_TICK)
				{
					this->setMarioState(MarioState::RunningOne);
					this->mClockRunning.restart();
				}
			}
			else if(this->mClockRunning.getElapsedTimeAsSeconds() > MARIO_RUNNING_TICK)
			{
				if(this->getMarioState() == MarioState::RunningOne)
					this->setMarioState(MarioState::RunningTwo);
				else if(this->getMarioState() == MarioState::RunningTwo)
					this->setMarioState(MarioState::RunningThree);
				this->mClockRunning.restart();
			}
		}
		else
		{
			this->setMarioState(MarioState::Idle);
		}
	}
}

void MarioGameMario::update( sf::Event p_event )
{
	
}

void MarioGameMario::draw()
{
	if(this->mSprite != NULL)
		Resource::resource->getApp()->draw(*this->mSprite);
}

void MarioGameMario::notifyMarioStateChanged()
{
	if(this->getMarioState() != MarioState::None)
	{
		if(this->mSprite != NULL)
		{
			delete this->mSprite;
			this->mSprite = NULL;
		}

		switch(this->mMarioState)
		{
		case Idle:
			this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIOIDLE);
			break;

		case RunningOne:
			this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIORUNONE);
			break;

		case RunningTwo:
			this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIORUNTWO);
			break;

		case RunningThree:
			this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIORUNTHREE);
			break;

		case Jumping:
			this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIOJUMP);
			break;

		default:
			this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIOIDLE);
			break;
		}
		ToolsImage::setSpriteOriginCenter(this->mSprite);
		if(this->mMarioDirection == MARIO_DIRECTION_RIGHT)
			this->mSprite->setScale(1, 1);
		else
			this->mSprite->setScale(-1, 1);
	}
}

void MarioGameMario::BeginContact( b2Contact* p_contact, UserDataIndex p_index )
{
	b2WorldManifold worldManifold;
	p_contact->GetWorldManifold(&worldManifold);
	if(this->getMarioState() == MarioState::Jumping && worldManifold.points[0].y < this->mBody->GetPosition().y && this->mBody->GetLinearVelocity().y <= 0)
		this->setMarioState(MarioState::Idle);
}

void MarioGameMario::PreSolve( b2Contact* p_contact, const b2Manifold* p_oldManifold, UserDataIndex p_index )
{
	
}
