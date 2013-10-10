#include "MarioGameMario.h"
#include "SpriteParameterFactory.h"

//*************************************************************
// Define
//*************************************************************
#define MARIO_INITAL_POSITIONX		50
#define MARIO_INITAL_POSITIONY		50


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameMario::MarioGameMario( MarioGame* p_game )
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
	shapeBox.SetAsBox(MARIOGAME_MARIO_WIDTH / 2, MARIOGAME_MARIO_HEIGHT / 2);

	// Define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shapeBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	this->mBody->CreateFixture(&fixtureDef);
	//this->mBody->ApplyLinearImpulse(b2Vec2(20,0), body->GetWorldCenter());

	// Test
	this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_MARIOIDLE);
}

MarioGameMario::~MarioGameMario(void)
{
	if(this->mSprite != NULL)
		delete this->mSprite;

	if(this->mWorld != NULL && this->mBody != NULL)
		this->mWorld->DestroyBody(this->mBody);
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameMario::update()
{
	b2Vec2 bodyPosition = this->mBody->GetPosition();
	this->mSprite->setPosition(	this->mGame->getX() + bodyPosition.x - MARIOGAME_MARIO_WIDTH / 2, 
								this->mGame->getBottomY() - bodyPosition.y - MARIOGAME_MARIO_HEIGHT / 2);
}

void MarioGameMario::update( sf::Event p_event )
{
	
}

void MarioGameMario::draw()
{
	if(this->mSprite != NULL)
		Resource::resource->getApp()->draw(*this->mSprite);
}
