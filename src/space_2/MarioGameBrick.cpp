#include "MarioGameBrick.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBrick::MarioGameBrick( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlock(p_game, p_positionGrid)
{
	this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICK);
}

MarioGameBrick::~MarioGameBrick(void)
{
}
