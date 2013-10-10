#include "MarioGameBlock.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBlock::MarioGameBlock(MarioGame* p_game, sf::Vector2i p_positionGrid)
{
	this->mSprite = NULL;
	this->mGame = p_game;
	this->mPositionGrid = p_positionGrid;
	this->mWorld = p_game->getWorld();

	// Define body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(this->mPositionGrid.x * MARIOGAME_BLOCK_WIDTH + 0.5 * MARIOGAME_BLOCK_WIDTH, this->mPositionGrid.y * MARIOGAME_BLOCK_HEIGHT + 0.5 * MARIOGAME_BLOCK_HEIGHT);
	this->mBody = this->mWorld->CreateBody(&groundBodyDef);

	// Define shape
	b2PolygonShape groundBox;
	groundBox.SetAsBox(MARIOGAME_BLOCK_WIDTH / 2, MARIOGAME_BLOCK_HEIGHT / 2);
	this->mBody->CreateFixture(&groundBox, 0.0f);
}

MarioGameBlock::~MarioGameBlock(void)
{
	if(this->mSprite != NULL)
		delete this->mSprite;

	if(this->mWorld != NULL && this->mBody != NULL)
		this->mWorld->DestroyBody(this->mBody);
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBlock::update()
{
	b2Vec2 bodyPosition = this->mBody->GetPosition();
	this->mSprite->setPosition(	this->mGame->getX() + bodyPosition.x - MARIOGAME_BLOCK_WIDTH / 2, 
								this->mGame->getBottomY() - bodyPosition.y - MARIOGAME_BLOCK_HEIGHT / 2);
}

void MarioGameBlock::draw()
{
	if(this->mSprite != NULL)
		Resource::resource->getApp()->draw(*this->mSprite);
}
