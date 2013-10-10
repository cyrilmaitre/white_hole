#include "MarioGameGround.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameGround::MarioGameGround( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlock(p_game, p_positionGrid)
{
	this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_GROUND);
}

MarioGameGround::~MarioGameGround(void)
{
}
