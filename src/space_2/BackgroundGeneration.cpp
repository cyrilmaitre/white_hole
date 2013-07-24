#include "BackgroundGeneration.h"
#include "SpriteParameterFactory.h"

//*************************************************************
// Define
//*************************************************************
#define BACKGROUND_ITEMS	40
#define BACKGROUND_SIZE		150


//*************************************************************
// Constructor - Destructor
//*************************************************************
BackgroundGeneration::BackgroundGeneration(void)
{
}

BackgroundGeneration::~BackgroundGeneration(void)
{
}


//*************************************************************
// Methodes
//*************************************************************
BackgroundSpace* BackgroundGeneration::getBackgroundSpace( sf::Vector2i p_size )
{
	// Setup
	SpriteParameter *spriteParameter = SpriteParameterFactory::getSpriteParameterSpaceBackground();
	int columnCount = 0;
	int lineCount = 0;

	columnCount = p_size.x / spriteParameter->getSpriteWidth();
	if(p_size.x % spriteParameter->getSpriteWidth() != 0)
		columnCount++;

	lineCount = p_size.y / spriteParameter->getSpriteHeight();
	if(p_size.y % spriteParameter->getSpriteHeight() != 0)
		lineCount++;

	// Generation
	BackgroundSpace *tmpBackgroundSpace = new BackgroundSpace(p_size.x, p_size.y, columnCount, lineCount);

	// Tiles
	for(int i = 0; i < columnCount; i++)
	{
		for(int j = 0; j < lineCount; j++)
		{
			tmpBackgroundSpace->setBackgroundTile(rand() % BACKGROUND_ITEMS, i, j);
		}
	}

	// Return
	return tmpBackgroundSpace;
}
