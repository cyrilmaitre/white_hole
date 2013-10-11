#include "MarioGameBrick.h"
#include "SpriteParameterFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBrick::MarioGameBrick( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlockActive(p_game, p_positionGrid)
{
	this->setUserDataType(UserDataType::Brick);

	this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BRICK);
	ToolsImage::setSpriteOriginCenter(this->mSprite);
}

MarioGameBrick::~MarioGameBrick(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBrick::update()
{
	MarioGameBlockActive::update();	
}

