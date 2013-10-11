#include "MarioGameBonus.h"
#include "SpriteParameterFactory.h"
#include "ToolsImage.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGameBonus::MarioGameBonus( MarioGame* p_game, sf::Vector2i p_positionGrid ) : MarioGameBlock(p_game, p_positionGrid)
{
	this->mActive = true;
	this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSACTIVE);
	ToolsImage::setSpriteOriginCenter(this->mSprite);
}

MarioGameBonus::~MarioGameBonus(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool MarioGameBonus::isActive()
{
	return this->mActive;
}

void MarioGameBonus::setActive( bool p_active )
{
	if(this->mActive != p_active)
	{
		this->mActive = p_active;
		this->notifyActiveChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarioGameBonus::notifyActiveChanged()
{
	if(this->mSprite != NULL)
	{
		delete this->mSprite;
		this->mSprite = NULL;
	}

	if(this->isActive())
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSACTIVE);
	else
		this->mSprite = SpriteParameterFactory::getSpriteParameterMarioGame()->getSpritePtr(MARIOGAME_SPRITE_BONUSINACTIVE);
}
